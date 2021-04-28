/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/28 11:19:54 by tvanelst         ###   ########.fr       */
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
	const double	b = 2 * scalar_product(ray.direction, vec_difference(ray.o, sphere.o));
	const double	c = get_norm2(vec_difference(ray.o, sphere.o)) - sphere.radius * sphere.radius;
	const double	delta = b * b - 4 * c;
	const double	t1 = (-b - sqrt(delta)) / 2;
	const double	t2 = (-b + sqrt(delta)) / 2;

	if (delta < 0 || t2 < 0)
		return (0);
	if (t1 > 0)
		*t = t1;
	else
		*t = t2;
	*p = vec_sum(ray.o, vec_product(ray.direction, *t));
	*n = get_normalized(vec_difference(*p, sphere.o));
	return (1);
}

int get_closest_intersection(t_ray ray, t_scene scene, t_vec *p, t_vec *n)
{
	t_vec	p_local;
	t_vec	n_local;
	int		i;
	double	t;
	double	min_t;
	int		return_value;

	return_value = 0;
	min_t = 1E99;
	i = 0;
	while (i++ < 6)
	{
		if (intersection(ray, scene.spheres[i - 1], &p_local, &n_local, &t))
		{
			if (t < min_t)
			{
				return_value = i;
				min_t = t;
				*p = p_local;
				*n = n_local;
			}
		}
	}
	return (return_value);
}

void	range_0_255(int *a)
{
	if (*a > 255)
		*a = 255;
	else if (*a < 0)
		*a = 0;
}

int	create_trgb(int t, int r, int g, int b)
{
	range_0_255(&t);
	range_0_255(&r);
	range_0_255(&g);
	range_0_255(&b);
	return(t << 24 | r << 16 | g << 8 | b);
}

t_scene	create_scene()
{
	t_scene			scene;

	scene.ligths[0] = (t_light){{15, 70, -30}, 1000000};
	scene.spheres[0] = (t_sphere){{0, 0, -55}, 20, {1, 0, 0}};
	scene.spheres[1] = (t_sphere){{0, -2020, 0}, 2000, {1, 1, 1}};
	scene.spheres[2] = (t_sphere){{0, 2000 + 100, 0}, 2000, {1, 1, 1}};
	scene.spheres[3] = (t_sphere){{-2020, 0, 0}, 2000, {0, 1, 0}};
	scene.spheres[4] = (t_sphere){{2020, 0, 0}, 2000, {0, 0, 1}};
	scene.spheres[5] = (t_sphere){{0, 0, -2050}, 2000, {0, 1, 1}};
	return (scene);
}

void	draw_pixel(t_vec n, t_vec p, t_light light, t_sphere sphere, t_data *data, t_point pixel)
{
	t_vec			pixel_light;
	int				color;
	double			tmp;

	tmp = scalar_product(get_normalized(vec_difference(light.o, p)), n) / get_norm2(vec_difference(light.o, p));
	if (tmp < 0)
		tmp = 0;
	pixel_light = vec_product(sphere.albedo ,light.intensity * tmp);
	color = create_trgb(0, pixel_light.x, pixel_light.y, pixel_light.z);
	my_mlx_pixel_put(data, pixel, color);
}

static t_vec	get_ray_direction(t_point resolution, t_point pixel, double fov)
{
	t_vec			direction;

	direction.x = pixel.x - resolution.x / 2;
	direction.y = pixel.y - resolution.y / 2;
	direction.z = - resolution.x / (2 * tan(fov / 2));
	normalise(&direction);
	return (direction);
}

int	display_stuff(t_point resolution, t_data *data)
{
	t_point			pixel;
	t_ray			ray;
	t_scene			scene;
	t_vec			p;
	t_vec			n;
	int				i;

	scene = create_scene();
	ray.o = (t_vec){0, 0, 0};
	pixel.y = resolution.y;
	while (--pixel.y >= 0)
	{
		pixel.x = resolution.x;
		while (--pixel.x >= 0)
		{
			ray.direction = get_ray_direction(resolution, pixel, 60 * M_PI / 180);
			i = get_closest_intersection(ray, create_scene(), &p, &n);
			if (i)
				draw_pixel(n, p, scene.ligths[0], scene.spheres[i - 1], data, (t_point){pixel.x, resolution.y - pixel.y - 1});
		}
	}
	return (0);
}

int	main(void)
{
	void			*mlx;
	t_data			img;
	void			*window;
	const t_point	resolution = {1024, 1024};

	mlx = mlx_init();
	if (!mlx)
		return (-1);
	window = mlx_new_window(mlx, resolution.x, resolution.y, "mini_rt");
	img.img = mlx_new_image(mlx, resolution.x, resolution.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	display_stuff(resolution, &img);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}
