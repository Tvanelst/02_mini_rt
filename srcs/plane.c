/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 10:22:20 by tvanelst          #+#    #+#             */
/*   Updated: 2021/06/28 16:34:59 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_pl(t_array *arr, char **ptr)
{
	t_plane	*el;

	el = (t_plane *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->o, a_to_v},
			{&el->orientation, a_to_v}, {&el->color, a_to_v}}));
}

int	pl_intersection(t_ray ray, t_plane pl, t_intersection *x)
{
	const double	a = vec_dot(vec_d(pl.o, ray.o), pl.orientation);
	const double	b = vec_dot(ray.direction, pl.orientation);
	const double	t = a / b;

	if (!b || t <= 0 || t >= x->d)
		return (0);
	x->d = t;
	x->p = vec_s(ray.o, vec_p(ray.direction, x->d));
	if (b > 0)
		x->n = vec_p(pl.orientation, -1);
	else
		x->n = pl.orientation;
	x->color = pl.color;
	x->object = plane;
	return (1);
}

int	all_pl_x(t_ray ray, t_array pl_array, t_intersection *x, double l_d)
{
	const t_plane	*planes = pl_array.ptr;
	size_t			i;

	i = -1;
	while (++i < pl_array.size)
		if (pl_intersection(ray, planes[i], x) && x->d * x->d < l_d)
			return (1);
	return (0);
}
