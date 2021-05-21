/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:59 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/21 18:37:59 by tvanelst         ###   ########.fr       */
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
	t_vec			p[4];
	t_intersection	x2;
	int				i;

	x2 = *x;
	i = -1;
	normalise(&sq.orientation);
	while (++i < 4)
	{
		p[i] = vec_d((t_vec){sq.o.x + sq.size / 2 - (sq.size * (i / 2)),
				sq.o.y + sq.size / 2 - (sq.size * (i % 2)), sq.o.z}, sq.o);
		normalise(p + i);
		if (sq.orientation.z != 1)
			apply_direction(p + i, sq.orientation);
		p[i] = vec_s(sq.o, vec_p(p[i], sqrt(2 * pow(sq.size / 2, 2))));
	}
	if (tr_intersection(ray, (t_triangle){p[0], p[1], p[2], sq.color}, &x2)
		|| tr_intersection(ray, (t_triangle){p[3], p[1], p[2], sq.color}, &x2))
	{
		*x = x2;
		x->n = sq.orientation;
		x->object = square;
		return (1);
	}
	return (0);
}

int	all_sq_x(t_ray ray, t_array sq_array, t_intersection *x, double l_d)
{
	const t_square	*squares = sq_array.ptr;
	size_t			i;

	i = -1;
	while (++i < sq_array.size)
		if (sq_intersection(ray, squares[i], x) && x->d * x->d < l_d)
			return (1);
	return (0);
}
