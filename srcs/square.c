/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:59 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/10 20:48:38 by tvanelst         ###   ########.fr       */
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
/* 	double	diagonale = sqrt(2 * sq.size);
	t_vec	corners[4];

	corners */
	if (pl_intersection(ray, (t_plane){sq.o, sq.orientation, sq.color}, x)
		&& (-sq.size < x->p.y - sq.o.y || x->p.y + sq.o.y < sq.size))
		return (1);
	return (0);
		//check if intersection in plane
}