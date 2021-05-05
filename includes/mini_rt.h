/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:24:14 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/05 17:14:18 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "../minilibx_opengl_20191021/mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "struct.h"
# include "sphere.h"
# include "square.h"
# include "plane.h"
# include "triangle.h"
# include "cylinder.h"
# include "camera.h"
# include "light.h"

typedef enum s_convertion
{
	a_to_v,
	a_to_d,
	a_to_i
}			t_convertion;

typedef struct s_scene
{
	t_array	resolution;
	t_array	amb_light;
	t_array	lights;
	t_array	cameras;
	t_array	spheres;
	t_array	planes;
	t_array	squares;
	t_array	cylinders;
	t_array	triangles;
}				t_scene;

typedef struct s_tuple
{
	char	*str;
	t_array	*arr;
	size_t	size;
	int		(*func)(t_array *arr, char **ptr);
}				t_tuple;

typedef struct s_tuple2
{
	void			*property;
	t_convertion	i;
}					t_tuple2;

int		create_trgb(int t, int r, int g, int b);
int		key_hook(int keycode, t_vars *vars);
int		create_scene(int fd, t_scene *s);
void	compute_pixel(t_ray ray, t_scene *s, t_point pixel, t_img *data);
int		save_bmp(t_img *img, t_point *r);
int		create_element(char **ptr, t_tuple2 *tab);
int		add_r(t_array *arr, char **ptr);
int		add_amb_l(t_array *arr, char **ptr);

#endif