/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:24:14 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/29 10:37:15 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "../minilibx_opengl_20191021/mlx.h"
# include "../libft/libft.h"
# include "../libft/ft_vec.h"
# include <stdio.h>
# include <limits.h>
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

typedef struct s_ray
{
	t_vec	o;
	t_vec	direction;
}			t_ray;

typedef struct s_sphere
{
	t_vec	c;
	double	r;
	t_vec	color;
}			t_sphere;

typedef struct s_planes
{
	t_vec	o;
	t_vec	orientation;
	t_vec	color;
}			t_planes;

typedef struct s_squares
{
	t_vec	o;
	t_vec	orientation;
	t_vec	color;
	double	size;
}			t_squares;

typedef struct s_cylinders
{
	t_vec	o;
	t_vec	orientation;
	t_vec	color;
	double	diameter;
	double	height;
}			t_cylinders;

typedef struct s_triangles
{
	t_vec	o1;
	t_vec	o2;
	t_vec	o3;
	t_vec	color;
	double	diameter;
	double	height;
}			t_triangles;

typedef struct s_light
{
	t_vec	o;
	double	intensity;
	t_vec	color;
}			t_light;

typedef struct s_camera
{
	t_vec	o;
	t_vec	direction;
	int		fov;
}				t_camera;

typedef struct s_scene
{
	t_point		resolution;
	t_light		amb_light;
	t_light		ligths[2];
	t_camera	cameras[1];
	t_sphere	*spheres;
	t_planes	planes[1];
	t_squares	squares[1];
	t_cylinders	cylinders[1];
	t_triangles	triangles[1];
}				t_scene;

int	create_trgb(int t, int r, int g, int b);
#endif