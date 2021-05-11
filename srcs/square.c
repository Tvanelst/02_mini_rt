/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:59 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/11 17:16:56 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_sq(t_array *arr, char **ptr)
{
	t_square	*el;

	el = (t_square *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->o, a_to_v},
			{&el->orientation, a_to_v}, {&el->size, a_to_d},
			{&el->color, a_to_v}}));
}

int	sq_intersection(t_ray ray, t_square sq, t_intersection *x)
{
	const double	diagonale = sqrt(2 * sq.size);
	t_vec			corners[4];

	corners[0] = (t_vec){0, 0, 0};
	if (pl_intersection(ray, (t_plane){sq.o, sq.orientation, sq.color}, x)
		&& (-sq.size < x->p.y - sq.o.y || x->p.y + sq.o.y < sq.size)
		&& (-sq.size < x->p.x - sq.o.x || x->p.x + sq.o.x < sq.size)
		&& (-sq.size < x->p.z - sq.o.z || x->p.z + sq.o.z < sq.size))
		return (1);
	return (0);
}

int	all_sq_intersection(t_ray ray, t_array sq_array, t_intersection *x)
{
	const t_square	*squares = sq_array.ptr;
	size_t			i;

	i = -1;
	while (++i < sq_array.size)
		if (sq_intersection(ray, squares[i], x))
			return (1);
	return (0);
}
