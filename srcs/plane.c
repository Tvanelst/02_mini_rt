/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 10:22:20 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/10 16:19:08 by tvanelst         ###   ########.fr       */
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
	const double	a = scalar_p(vec_d(pl.o, ray.o), pl.orientation);
	const double	b = scalar_p(ray.direction, pl.orientation);
	const double	t = a / b;

	if (!b || t < 0 || t >= x->d)
		return (0);
	x->d = t;
	x->p = vec_s(ray.o, vec_p(ray.direction, x->d));
	x->n = pl.orientation;
	return (1);
}
