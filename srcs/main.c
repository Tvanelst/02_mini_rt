/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/29 14:40:08 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	intersection(t_ray ray, t_sphere sphere, t_vec *p, t_vec *n, double *t)
{
	const double	b = 2 * scalar_product(ray.direction, vec_diff(ray.o, sphere.c));
	const double	c = get_norm2(vec_diff(ray.o, sphere.c)) - sphere.r * sphere.r;
	const double	delta = b * b - 4 * c;
	const double	t1 = (-b - sqrt(delta)) / 2;
	const double	t2 = (-b + sqrt(delta)) / 2;
	double			my_t;

	if (delta < 0 || t2 < 0)
		return (0);
	if (t1 > 0)
		my_t = t1;
	else
		my_t = t2;
	if (my_t < *t)
	{
		*t = my_t;
		*p = vec_sum(ray.o, vec_product(ray.direction, *t));
		*n = get_normalized(vec_diff(*p, sphere.c));
		return (1);
	}
	return (0);
}

void	draw_pixel(t_vec pixel_light, t_data *data, t_point pixel)
{
	int		color;
	char	*dst;
	size_t	offset;

	offset = (pixel.y * data->line_length + pixel.x * (data->bits_per_pixel / 8));
	color = create_trgb(0, pixel_light.x, pixel_light.y, pixel_light.z);
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

t_vec	get_pixel_light(t_scene *s, int closest, t_vec n, t_vec p)
{
	t_vec	vec_light_p;
	double	light_norm;
	t_vec	pixel_light;

	vec_light_p = vec_diff(s->ligths[0].o, p);
	light_norm = scalar_product(get_normalized(vec_light_p), n) / get_norm2(vec_light_p);
	if (light_norm < 0)
		light_norm = 0;
	pixel_light = vec_product(s->spheres[closest].color, s->ligths[0].intensity * light_norm);
	return (pixel_light);
}

void	compute_pixel(t_ray ray, t_scene *s, t_point pixel, t_data *data)
{
	t_vec	p;
	t_vec	n;
	double	t;
	int		i;
	int		closest;

	closest = -1;
	t = 1E99;
	i = -1;
	while (++i < 6)
		if (intersection(ray, s->spheres[i], &p, &n, &t))
			closest = i;
	if (closest >= 0)
	{
		pixel.y = s->resolution.y - pixel.y - 1;
		draw_pixel(get_pixel_light(s, closest, n, p), data, pixel);
	}
}

static t_vec	get_ray_direction(t_point resolution, t_point pixel, double fov)
{
	const double	r_fov = fov * M_PI / 180;
	t_vec			direction;

	direction.x = pixel.x - resolution.x / 2;
	direction.y = pixel.y - resolution.y / 2;
	direction.z = -resolution.x / (2 * tan(r_fov / 2));
	normalise(&direction);
	return (direction);
}

int	create_image(t_data *data, t_scene	*s)
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
			ray.direction = get_ray_direction(s->resolution, pixel, s->cameras->fov);
			compute_pixel(ray, s, pixel, data);
		}
	}
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*window;
	t_data	img;
	t_scene	s;
	t_vars	vars;

	s = create_scene();
	mlx = mlx_init();
	if (!mlx)
		return (-1);
	window = mlx_new_window(mlx, s.resolution.x, s.resolution.y, "mini_rt");
	img.img = mlx_new_image(mlx, s.resolution.x, s.resolution.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	create_image(&img, &s);
	vars.mlx = mlx;
	vars.win = window;
	mlx_key_hook(vars.win, &key_hook, &vars);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}
