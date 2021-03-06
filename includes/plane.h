/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:27:59 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/13 21:43:24 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include "struct.h"

typedef struct s_plane
{
	t_vec	o;
	t_vec	orientation;
	t_vec	color;
}			t_plane;

int		add_pl(t_array *arr, char **ptr);
int		pl_intersection(t_ray ray, t_plane pl, t_intersection *x);
int		all_pl_x(t_ray ray, t_array pl_array, t_intersection *x, double l_d);
#endif