/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:19:06 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/11 11:08:01 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "struct.h"

typedef struct s_sphere
{
	t_vec	c;
	double	r;
	t_vec	color;
}			t_sphere;

int	add_sp(t_array *arr, char **ptr);
int	sp_intersection(t_ray ray, t_sphere sp, t_intersection *x);
int	all_sp_intersection(t_ray ray, t_array sp_array, t_intersection *x);

#endif