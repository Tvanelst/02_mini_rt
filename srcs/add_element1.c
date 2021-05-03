/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_element1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:38:58 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/03 11:39:39 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_r(t_array *arr, char **ptr)
{
	t_point	*el;

	el = (t_point *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->x, 2},
			{&el->y, 2}}));
}

int	add_amb_l(t_array *arr, char **ptr)
{
	t_light	*el;

	el = (t_light *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->intensity, 1},
			{&el->color, 0}}));
}

int	add_sp(t_array *arr, char **ptr)
{
	t_sphere	*el;

	el = (t_sphere *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->c, 0},
			{&el->r, 1}, {&el->color, 0}}));
}

int	add_sq(t_array *arr, char **ptr)
{
	t_square	*el;

	el = (t_square *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->o, 0},
			{&el->orientation, 0}, {&el->size, 1}, {&el->color, 0}}));
}

int	add_l(t_array *arr, char **ptr)
{
	t_light	*el;

	el = (t_light *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->o, 0},
			{&el->intensity, 1}, {&el->color, 0}}));
}
