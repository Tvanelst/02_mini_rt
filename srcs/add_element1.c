/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_element1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:38:58 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/05 23:05:34 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_r(t_array *arr, char **ptr)
{
	t_point	*el;

	el = (t_point *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->x, a_to_i},
			{&el->y, a_to_i}}));
}

int	add_amb_l(t_array *arr, char **ptr)
{
	t_light	*el;

	el = (t_light *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->intensity, a_to_d},
			{&el->color, a_to_v}}));
}

int	add_sq(t_array *arr, char **ptr)
{
	t_square	*el;

	el = (t_square *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->o, a_to_v},
			{&el->orientation, a_to_v}, {&el->size, a_to_d},
			{&el->color, a_to_v}}));
}

int	add_l(t_array *arr, char **ptr)
{
	t_light	*el;

	el = (t_light *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->o, a_to_v},
			{&el->intensity, a_to_d}, {&el->color, a_to_v}}));
}
