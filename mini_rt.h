/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:24:14 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/28 11:12:48 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "minilibx_opengl_20191021/mlx.h"
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <unistd.h>
# define RED 0x00FF0000

typedef struct s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}			t_vec;

typedef struct s_ray
{
	t_vec	o;
	t_vec	direction;
}			t_ray;

typedef struct s_sphere
{
	t_vec	o;
	double	radius;
	t_vec	albedo;
}			t_sphere;

typedef struct s_light
{
	t_vec	o;
	double	intensity;
}			t_light;

typedef struct s_scene
{
	t_sphere	spheres[6];
	t_light		ligths[2];
	int			has_intersection;
}				t_scene;


t_vec	vec_sum(t_vec a, t_vec b);
t_vec	vec_difference(t_vec a, t_vec b);
t_vec	vec_product(t_vec a, float b);
t_vec	vector_quotient(t_vec a, float b);
double	scalar_product(t_vec a, t_vec b);
double	get_norm2(t_vec a);
void	normalise(t_vec *a);
t_vec	get_normalized(t_vec a);
#endif