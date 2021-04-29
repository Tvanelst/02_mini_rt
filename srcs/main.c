/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/29 15:35:01 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	get_ray_direction(t_scene *s, t_point pixel)
{
	const double	r_fov = s->cameras[0].fov * M_PI / 180;
	t_vec			direction;

	direction.x = pixel.x - s->resolution.x / 2;
	direction.y = pixel.y - s->resolution.y / 2;
	direction.z = -s->resolution.x / (2 * tan(r_fov / 2));
	normalise(&direction);
	return (direction);
}

int	create_image(t_img *img, t_scene *s)
{
	t_point			pixel;
	t_ray			ray;

	ray.o = (t_vec){0, 0, 0};
	pixel.y = s->resolution.y;
	while (--pixel.y >= 0)
	{
		pixel.x = s->resolution.x;
		while (--pixel.x >= 0)
		{
			ray.direction = get_ray_direction(s, pixel);
			compute_pixel(ray, s, pixel, img);
		}
	}
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*window;
	t_img	img;
	t_scene	s;
	t_vars	vars;

	s = create_scene();
	mlx = mlx_init();
	if (!mlx)
		return (-1);
	window = mlx_new_window(mlx, s.resolution.x, s.resolution.y, "mini_rt");
	img.img = mlx_new_image(mlx, s.resolution.x, s.resolution.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len,
			&img.endian);
	create_image(&img, &s);
	vars.mlx = mlx;
	vars.win = window;
	mlx_key_hook(vars.win, &key_hook, &vars);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}
