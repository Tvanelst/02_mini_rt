/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/14 16:10:11 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_ray	get_ray(t_scene *s, t_point pixel, size_t i)
{
	const double	r_fov = ((t_camera *)s->cameras.ptr)[i].fov * M_PI / 180;
	const t_point	*resolution = s->resolution.ptr;
	const t_camera	*cameras = s->cameras.ptr;
	t_ray			ray;

	ray.o = cameras[i].o;
	ray.direction.x = pixel.x - resolution->x / 2;
	ray.direction.y = pixel.y - resolution->y / 2;
	ray.direction.z = -resolution->x / (2 * tan(r_fov / 2));
	rotation_x(&ray.direction, i * M_PI / 2);
	/* ray.direction = vec_p_vec(ray.direction, normed(cameras[i].direction)); */
	normalise(&ray.direction);
	return (ray);
}

static void	create_image(t_img *img, t_scene *s, size_t i)
{
	t_point		pixel;
	t_ray		ray;

	pixel.y = ((t_point *)s->resolution.ptr)->y;
	while (--pixel.y >= 0)
	{
		pixel.x = ((t_point *)s->resolution.ptr)->x;
		while (--pixel.x >= 0)
		{
			ray = get_ray(s, pixel, i);
			compute_pixel(ray, s, pixel, img);
		}
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_img	*img;
	t_scene	s;
	t_point	*resolution;
	size_t	i;

	if (validate_input(argc, argv, &s, &mlx))
		return (-1);
	img = malloc(sizeof(*img) * s.cameras.size);
	if (!img)
		return (-1);
	resolution = ((t_point *)s.resolution.ptr);
	i = -1;
	while (++i < s.cameras.size)
	{
		img[i].img = mlx_new_image(mlx, resolution->x, resolution->y);
		img[i].addr = mlx_get_data_addr(img[i].img, &img[i].bits_per_pixel,
				&img[i].line_len, &img[i].endian);
		img[i].bmp = (argc == 3);
		create_image(img + i, &s, i);
	}
	if (img[0].bmp)
		return (save_bmp(img, resolution));
	window = mlx_new_window(mlx, resolution->x, resolution->y, "mini_rt");
	key_hook_setup(mlx, window, img, s.cameras.size);
	mlx_put_image_to_window(mlx, window, img[0].img, 0, 0);
	mlx_loop(mlx);
}
