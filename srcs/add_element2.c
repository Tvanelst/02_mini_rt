/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_element2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:38:55 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/03 11:40:09 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_c(t_array *arr, char **ptr)
{
	t_camera	*el;

	el = (t_camera *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->o, 0},
			{&el->direction, 0}, {&el->fov, 2}}));
}

int	add_pl(t_array *arr, char **ptr)
{
	t_planes	*el;

	el = (t_planes *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->o, 0},
			{&el->orientation, 0}, {&el->color, 0}}));
}

int	add_cy(t_array *arr, char **ptr)
{
	t_cylinders	*el;

	el = (t_cylinders *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->o, 0},
			{&el->orientation, 0}, {&el->diameter, 1}, {&el->height, 1},
			{&el->color, 0}}));
}

int	add_tr(t_array *arr, char **ptr)
{
	t_triangles	*el;

	el = (t_triangles *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->o1, 0},
			{&el->o2, 0}, {&el->o3, 0}, {&el->color, 0}}));
}
