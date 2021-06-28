/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/06/24 16:32:29 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	apply_direction(t_vec *a, t_vec b)
{
	double	left_right_angles;
	double	up_down_angle;
	t_vec	w;
	t_vec	tmp;

	if (b.x || b.z)
	{
		left_right_angles = acos(-b.z / sqrt(get_norm2((t_vec){b.x, 0, b.z})));
		if (b.x > 0)
			left_right_angles = -left_right_angles;
		rotation_y(a, left_right_angles);
	}
	if (b.y)
	{
		tmp = (t_vec){0, 0, -1};
		if (b.x || b .z)
			tmp = (t_vec){b.x, 0, b.z};
		normalise(&tmp);
		w = cross(tmp, (t_vec){0, 1, 0});
		normalise(&w);
		up_down_angle = acos(vec_dot(tmp, b));
		if (b.y < 0)
			up_down_angle = -up_down_angle;
		rotation_u(a, up_down_angle, w);
	}
}

t_ray	get_ray(t_scene *s, t_point pixel)
{
	const t_camera	*cameras = ((t_camera *)s->cameras.ptr);
	const double	r_fov = fmax(fmin(cameras->fov, 180), 0) * M_PI / 180;
	const t_point	*resolution = s->resolution.ptr;
	t_ray			ray;

	ray.o = cameras->o;
	ray.direction.x = pixel.x - resolution->x / 2;
	ray.direction.y = pixel.y - resolution->y / 2;
	ray.direction.z = -resolution->x / (2 * tan(r_fov / 2));
	normalise(&ray.direction);
	apply_direction(&ray.direction, cameras->direction);
	return (ray);
}

static void	create_image(void *mlx, t_img *img, t_scene *s)
{
	const t_point	*resolution = s->resolution.ptr;
	t_point			pixel;
	t_ray			ray;

	img->img = mlx_new_image(mlx, resolution->x, resolution->y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	pixel.y = resolution->y;
	normalise(&((t_camera *)s->cameras.ptr)[0].direction);
	while (--pixel.y >= 0)
	{
		pixel.x = resolution->x;
		while (--pixel.x >= 0)
		{
			ray = get_ray(s, pixel);
			compute_pixel(ray, s, pixel, img);
		}
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_img	img;
	t_scene	s;
	t_point	*resolution;

	validate_input(argc, argv, &s, &mlx);
	create_image(mlx, &img, &s);
	resolution = ((t_point *)s.resolution.ptr);
	window = mlx_new_window(mlx, resolution->x, resolution->y, "mini_rt");
	if (!window)
		handle_error(0, "impossible to create the window", &s);
	clear_scene(&s);
	key_hook_setup(mlx, window, &img, &s);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
