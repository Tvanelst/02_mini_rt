/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:19:31 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/11 17:28:25 by tvanelst         ###   ########.fr       */
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

int		cy_intersection(t_ray ray, t_cylinder cy, t_intersection *x)
{
	(void)ray;
	(void)cy;
	(void)x;
	return (0);
}

int		all_cy_intersection(t_ray ray, t_array cy_array, t_intersection *x)
{
	const t_cylinder	*cylinders = cy_array.ptr;
	size_t				i;

	i = -1;
	while (++i < cy_array.size)
		if (cy_intersection(ray, cylinders[i], x))
			return (1);
	return (0);
}
