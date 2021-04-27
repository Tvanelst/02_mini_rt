/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/28 00:11:02 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	my_mlx_pixel_put(t_data *data, t_point pixel, int color)
{
	char	*dst;

	dst = data->addr + (pixel.y * data->line_length + pixel.x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	intersection(t_ray ray, t_sphere sphere, t_vec *p, t_vec *n)
{
	const double	b = 2 * scalar_product(ray.direction, vector_difference(ray.o, sphere.o));
	const double	c = get_norm2(vector_difference(ray.o, sphere.o)) - sphere.radius * sphere.radius;
	const double	delta = b * b - 4 * c;
	const double	t1 = (-b - sqrt(delta)) / 2;
	const double	t2 = (-b + sqrt(delta)) / 2;
	double			t;

	if (delta < 0 || t2 < 0)
		return (0);
	if (t1 > 0)
		t = t1;
	else
		t = t2;
	*p = vector_sum(ray.o, vector_product(ray.direction, t));
	*n = get_normalized(vector_difference(*p, sphere.o));
	return (1);
}

int		create_trgb(int t, int r, int g, int b)
{
	if (t < 0)
		t = 0;
	else if (t > 255)
		t = 255;
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return(t << 24 | r << 16 | g << 8 | b);
}

/* t_scene	create_scene()
{
	const t_sphere	sphere = {{0, 0, -55}, 20, {1, 0, 0}};
	const t_light	light = {{15, 70, -30}, 1000000};
	t_scene			scene;

	scene.ligths = light
} */

void	draw_pixel(t_vec n, t_vec p, t_light light, t_sphere sphere, t_data *data, t_point pixel)
{
	t_vec			pixel_light;
	int				color;
	double			tmp;

	tmp = scalar_product(get_normalized(vector_difference(light.o, p)), n) / get_norm2(vector_difference(light.o, p));
	if (tmp < 0)
		tmp = 0;
	pixel_light = vector_product(sphere.albedo ,light.intensity * tmp);
	color = create_trgb(0, pixel_light.x, pixel_light.y, pixel_light.z);
	my_mlx_pixel_put(data, pixel, color);
}

static t_vec	get_ray_direction(t_point resolution, t_point pixel)
{
	t_vec			direction;
	const double	fov = 60 * M_PI / 180;

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
	t_sphere		sphere = {{0, 0, -55}, 20, {1, 0, 0}};
	t_light			light = {{15, 70, -30}, 1000000};
	t_vec			p;
	t_vec			n;

	ray.o = (t_vec){0, 0, 0};
	pixel.y = resolution.y;
	while (--pixel.y >= 0)
	{
		pixel.x = resolution.x;
		while (--pixel.x >= 0)
		{
			ray.direction = get_ray_direction(resolution, pixel);
			if (intersection(ray, sphere, &p, &n))
				draw_pixel(n, p, light, sphere, data, (t_point){pixel.x, resolution.y - pixel.y - 1});
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
