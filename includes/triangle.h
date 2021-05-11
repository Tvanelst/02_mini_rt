/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:33:09 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/11 11:42:45 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H
# include "struct.h"

typedef struct s_triangle
{
	t_vec	o1;
	t_vec	o2;
	t_vec	o3;
	t_vec	color;
}			t_triangle;

int		add_tr(t_array *arr, char **ptr);
int		tr_intersection(t_ray ray, t_triangle tr, t_intersection *x);
int		all_tr_intersection(t_ray ray, t_array tr_array, t_intersection *x);

#endif