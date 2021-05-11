/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:28:51 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/11 17:19:13 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "mini_rt.h"

typedef struct s_cylinder
{
	t_vec	o;
	t_vec	orientation;
	t_vec	color;
	double	diameter;
	double	height;
}			t_cylinder;

int		add_cy(t_array *arr, char **ptr);
int		cy_intersection(t_ray ray, t_cylinder cy, t_intersection *x);
int		all_cy_intersection(t_ray ray, t_array sq_array, t_intersection *x);

#endif