/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/28 18:15:12 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	my_mlx_pixel_put(t_data *data, t_point pixel, int color)
{
	char	*dst;

	dst = data->addr + (pixel.y * data->line_length + pixel.x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	intersection(t_ray ray, t_sphere sphere, t_vec *p, t_vec *n, double *t)
{
	const double	b = 2 * scalar_product(ray.direction, vec_difference(ray.o, sphere.c));
	const double	c = get_norm2(vec_difference(ray.o, sphere.c)) - sphere.r * sphere.r;
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
		*n = get_normalized(vec_difference(*p, sphere.c));
		return (1);
	}
	return (0);
}

void	keep_in_range(int *a, int min, int max)
{
	if (*a > max)
		*a = max;
	else if (*a < min)
		*a = min;
}

int	create_trgb(int t, int r, int g, int b)
{
	keep_in_range(&t, 0, 255);
	keep_in_range(&r, 0, 255);
	keep_in_range(&g, 0, 255);
	keep_in_range(&b, 0, 255);
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_pixel(t_light light, t_vec object_color, t_data *data, t_point pixel, double	light_norm)
{
	t_vec	pixel_light;
	int		color;

	pixel_light = vec_product(object_color, light.intensity * light_norm);
	color = create_trgb(0, pixel_light.x, pixel_light.y, pixel_light.z);
	my_mlx_pixel_put(data, pixel, color);
}

void	get_closest_intersection(t_ray ray, t_scene s, t_point pixel, t_data *data)
{
	t_vec	p;
	t_vec	n;
	double	t;
	int		i;
	int		closest;
	t_vec	vec_light_p;
	double	light_norm;

	closest = 0;
	t = 1E99;
	i = -1;
	while (++i < 6)
		if (intersection(ray, s.spheres[i], &p, &n, &t))
			closest = i;
	if (closest >= 0)
	{
		vec_light_p = vec_difference(s.ligths[0].o, p);
		light_norm = scalar_product(get_normalized(vec_light_p), n) / get_norm2(vec_light_p);
		if (light_norm < 0)
			light_norm = 0;
		draw_pixel(s.ligths[0], s.spheres[closest].color, data, pixel, light_norm);
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

int	create_image(t_data *data, t_scene	s)
{
	t_point			pixel;
	t_ray			ray;

	ray.o = (t_vec){0, 0, 0};
	pixel.y = s.resolution.y;
	while (--pixel.y >= 0)
	{
		pixel.x = s.resolution.x;
		while (--pixel.x >= 0)
		{
			ray.direction = get_ray_direction(s.resolution, pixel, s.cameras->fov);
			get_closest_intersection(ray, s, (t_point){pixel.x, s.resolution.y - pixel.y - 1}, data);
		}
	}
	return (0);
}

t_scene	create_scene(void)
{
	t_scene			scene;

	scene.resolution = (t_point){1024, 1024};
	scene.cameras[0] = (t_camera){{0, 0, 0}, {0, 0, -1}, 60};
	scene.ligths[0] = (t_light){{15, 60, -10}, 1000000, {1, 0, 1}};
	scene.spheres[0] = (t_sphere){{0, 0, -55}, 20, {1, 0, 0}};
	scene.spheres[1] = (t_sphere){{0, -2020, 0}, 2000, {1, 1, 1}};
	scene.spheres[2] = (t_sphere){{0, 2030, 0}, 2000, {1, 1, 1}};
	scene.spheres[3] = (t_sphere){{-2020, 0, 0}, 2000, {0, 1, 0}};
	scene.spheres[4] = (t_sphere){{2020, 0, 0}, 2000, {0, 0, 1}};
	scene.spheres[5] = (t_sphere){{0, 0, -2050}, 2000, {0, 1, 1}};
	return (scene);
}

int	main(void)
{
	void			*mlx;
	void			*window;
	t_data			img;
	t_scene			s;

	s = create_scene();
	mlx = mlx_init();
	if (!mlx)
		return (-1);
	window = mlx_new_window(mlx, s.resolution.x, s.resolution.y, "mini_rt");
	img.img = mlx_new_image(mlx, s.resolution.x, s.resolution.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	create_image(&img, s);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}