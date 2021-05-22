/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:19:31 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/22 11:04:35 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_cy(t_array *arr, char **ptr)
{
	t_cylinder	*el;

	el = (t_cylinder *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->o, a_to_v},
			{&el->orientation, a_to_v}, {&el->diameter, a_to_d},
			{&el->height, a_to_d}, {&el->color, a_to_v}}));
}

int	cy_intersection_2(double a, double b, double c, t_intersection *x)
{
	const double	delta = sqrt(b * b - 4 * a * c);
	const double	t2 = (-b + delta) / (2 * a);
	double			my_t;

	if (delta < 0 || t2 < 0)
		return (0);
	my_t = (-b - delta) / (2 * a);
	if (my_t <= 0)
		my_t = t2;
	if (my_t < x->d)
	{
		x->d = my_t;
		return (1);
	}
	return (0);
}

int	cy_intersection(t_ray ray, t_cylinder cy, t_intersection *x)
{
	const t_vec		AOxAB = cross(vec_d(ray.o, cy.o), cy.orientation);
	const t_vec		VxAB = cross(ray.direction, cy.orientation);
	const double	a = get_norm2(VxAB);
	const double	b = 2 * vec_dot(VxAB, AOxAB);
	const double	c = get_norm2(AOxAB) - (pow(cy.diameter / 2, 2)
						* get_norm2(cy.orientation));

	if (!cy_intersection_2(a, b, c, x))
		return (0);
	x->p = vec_s(ray.o, vec_p(ray.direction, x->d));
	x->n = vec_p(x->p, -1);
	x->color = cy.color;
	x->object = cylinder;
	return (1);
}

int	all_cy_x(t_ray ray, t_array cy_array, t_intersection *x, double l_d)
{
	const t_cylinder	*cylinders = cy_array.ptr;
	size_t				i;

	i = -1;
	while (++i < cy_array.size)
		if (cy_intersection(ray, cylinders[i], x) && x->d * x->d < l_d)
			return (1);
	return (0);
}
