/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/21 22:04:39 by tvanelst         ###   ########.fr       */
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

t_ray	get_ray(t_scene *s, t_point pixel, size_t i)
{
	const double	r_fov = ((t_camera *)s->cameras.ptr)[i].fov * M_PI / 180;
	const t_point	*resolution = s->resolution.ptr;
	t_camera		*cameras;
	t_ray			ray;

	cameras = s->cameras.ptr;
	ray.o = cameras[i].o;
	ray.direction.x = pixel.x - resolution->x / 2;
	ray.direction.y = pixel.y - resolution->y / 2;
	ray.direction.z = -resolution->x / (2 * tan(r_fov / 2));
	normalise(&ray.direction);
	normalise(&cameras[i].direction);
	apply_direction(&ray.direction, cameras[i].direction);
	return (ray);
}

static void	create_images(void *mlx, t_img *img, t_scene *s)
{
	const t_point	*resolution = s->resolution.ptr;
	t_point			pixel;
	t_ray			ray;
	size_t			i;

	i = -1;
	while (++i < s->cameras.size)
	{
		img[i].img = mlx_new_image(mlx, resolution->x, resolution->y);
		img[i].addr = mlx_get_data_addr(img[i].img, &img[i].bits_per_pixel,
				&img[i].line_len, &img[i].endian);
		pixel.y = resolution->y;
		while (--pixel.y >= 0)
		{
			pixel.x = resolution->x;
			while (--pixel.x >= 0)
			{
				ray = get_ray(s, pixel, i);
				compute_pixel(ray, s, pixel, &img[i]);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_img	*imgs;
	t_scene	s;
	t_point	*resolution;

	validate_input(argc, argv, &s, &mlx);
	imgs = malloc(sizeof(*imgs) * s.cameras.size);
	if (!imgs)
		handle_error(0, "malloc error", &s);
	create_images(mlx, imgs, &s);
	if (s.bmp)
		return (save_bmp(imgs, &s));
	resolution = ((t_point *)s.resolution.ptr);
	window = mlx_new_window(mlx, resolution->x, resolution->y, "mini_rt");
	clear_scene(&s);
	key_hook_setup(mlx, window, imgs, &s);
	mlx_put_image_to_window(mlx, window, imgs[0].img, 0, 0);
	mlx_loop(mlx);
}
