/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:28:24 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/13 21:43:39 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H
# include "struct.h"

typedef struct s_square
{
	t_vec	o;
	t_vec	orientation;
	t_vec	color;
	double	size;
}			t_square;

int		add_sq(t_array *arr, char **ptr);
int		sq_intersection(t_ray ray, t_square sq, t_intersection *x);
int		all_sq_x(t_ray ray, t_array sq_array, t_intersection *x, double l_d);

#endif