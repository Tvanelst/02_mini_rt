/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:24:14 by tvanelst          #+#    #+#             */
/*   Updated: 2021/06/08 23:32:28 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "../minilibx_mms_20200219/mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "struct.h"
# include "sphere.h"
# include "plane.h"
# include "cylinder.h"
# include "camera.h"
# include "light.h"

typedef enum e_convertion
{
	a_to_v,
	a_to_d,
	a_to_i
}			t_convertion;

typedef enum e_object
{
	none,
	sphere,
	plane,
	cylinder,
	camera,
	light,
	resolution
}			t_object;

typedef struct s_scene
{
	t_array	resolution;
	t_array	amb_light;
	t_array	lights;
	t_array	cameras;
	t_array	spheres;
	t_array	planes;
	t_array	cylinders;
}			t_scene;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_img	*img;
	t_scene	*s;

}				t_vars;

typedef struct s_obj_creator
{
	char	*str;
	t_array	*arr;
	size_t	size;
	int		(*func)(t_array *arr, char **ptr);
}				t_obj_creator;

typedef struct s_obj_property
{
	void			*property;
	t_convertion	i;
}					t_obj_property;

void	validate_input(int argc, char **argv, t_scene *s, void **mlx);
int		create_element(char **ptr, t_obj_property *tab);
int		add_r(t_array *arr, char **ptr);
int		add_amb_l(t_array *arr, char **ptr);
void	compute_pixel(t_ray ray, t_scene *s, t_point pixel, t_img *data);
int		create_trgb(int t, int r, int g, int b);
int		save_bmp(t_img *img, t_scene *s);
void	key_hook_setup(void *mlx, void *window, t_img *img, t_scene *s);
void	clear_scene(t_scene *s);
void	handle_error(char **ptr, char *str, t_scene *s);
void	apply_direction(t_vec *a, t_vec b);

#endif