/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:19:31 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/24 13:32:08 by tvanelst         ###   ########.fr       */
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

static int	is_in_cylinder(t_cylinder cy, t_ray ray, double *t, double my_t)
{
	const t_plane	plane = {cy.o, cy.orientation, cy.color};
	t_intersection	x2;

	ray.o = vec_s(ray.o, vec_p(ray.direction, my_t));
	ray.direction = vec_p(cy.orientation, -1);
	x2.d = cy.height;
	if (!pl_intersection(ray, plane, &x2))
		return (0);
	*t = x2.d;
	return (1);
}

static int	cy_intersection_2(double quadra[2],
				t_intersection *x, t_cylinder cy, t_ray ray)
{
	const double	t2 = quadra[0] + quadra[1];
	double			my_t;
	double			t3;

	if (quadra[1] < 0 || t2 < 0)
		return (0);
	my_t = quadra[0] - quadra[1];
	if (my_t < 0 || !is_in_cylinder(cy, ray, &t3, my_t))
	{
		my_t = t2;
		if (!is_in_cylinder(cy, ray, &t3, my_t))
			return (0);
	}
	if (my_t < x->d)
	{
		x->d = my_t;
		x->p = vec_s(ray.o, vec_p(ray.direction, x->d));
		x->n = normed(vec_d(x->p, vec_s(cy.o, vec_p(cy.orientation, t3))));
		x->color = cy.color;
		x->object = cylinder;
		return (1);
	}
	return (0);
}

int	cy_intersection(t_ray ray, t_cylinder cy, t_intersection *x)
{
	const t_vec		AOxAB = cross(vec_d(ray.o, cy.o), cy.orientation);
	const t_vec		VxAB = cross(ray.direction, cy.orientation);
	const double	a = 2 * get_norm2(VxAB);
	const double	b = 2 * vec_dot(VxAB, AOxAB);
	const double	c = get_norm2(AOxAB) - (pow(cy.diameter / 2, 2)
						* get_norm2(cy.orientation));

	normalise(&cy.orientation);
	return (cy_intersection_2(
			(double []){-b / a, (sqrt(b * b - 2 * a * c)) / a}, x, cy, ray));
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
