/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_element2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:38:55 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/05 17:14:18 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_c(t_array *arr, char **ptr)
{
	t_camera	*el;

	el = (t_camera *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->o, a_to_v},
			{&el->direction, a_to_v}, {&el->fov, a_to_i}}));
}

int	add_pl(t_array *arr, char **ptr)
{
	t_plane	*el;

	el = (t_plane *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->o, a_to_v},
			{&el->orientation, a_to_v}, {&el->color, a_to_v}}));
}

int	add_cy(t_array *arr, char **ptr)
{
	t_cylinders	*el;

	el = (t_cylinders *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->o, a_to_v},
			{&el->orientation, a_to_v}, {&el->diameter, a_to_d}, {&el->height, a_to_d},
			{&el->color, a_to_v}}));
}
