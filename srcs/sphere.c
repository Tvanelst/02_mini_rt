/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:16:17 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/24 10:50:45 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_sp(t_array *arr, char **ptr)
{
	t_sphere	*el;

	el = (t_sphere *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->c, a_to_v},
			{&el->r, a_to_d}, {&el->color, a_to_v}}));
}

int	sp_intersection(t_ray ray, t_sphere sp, t_intersection *x)
{
	const double	b = 2 * vec_dot(ray.direction, vec_d(ray.o, sp.c));
	const double	c = get_norm2(vec_d(ray.o, sp.c)) - sp.r * sp.r;
	const double	delta = sqrt(b * b - 4 * c);
	double			my_t;

	if (delta < 0)
		return (0);
	my_t = (-b - delta) / 2;
	if (my_t <= 0)
		my_t += delta;
	if (0 < my_t && my_t < x->d)
	{
		x->d = my_t;
		x->p = vec_s(ray.o, vec_p(ray.direction, x->d));
		x->n = normed(vec_d(x->p, sp.c));
		x->color = sp.color;
		x->object = sphere;
		return (1);
	}
	return (0);
}

int	all_sp_x(t_ray ray, t_array sp_array, t_intersection *x, double l_d)
{
	const t_sphere	*spheres = sp_array.ptr;
	size_t			i;

	i = -1;
	while (++i < sp_array.size)
		if (sp_intersection(ray, spheres[i], x) && x->d * x->d < l_d)
			return (1);
	return (0);
}
