/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/27 22:34:00 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	display_vector(t_vec a)
{
	printf("vector.x = %f\n", a.x);
	printf("vector.y = %f\n", a.y);
	printf("vector.z = %f\n", a.z);
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


int	display_stuff(t_point resolution, t_data *data)
{
	int				i;
	int				j;
	t_ray			ray;
	const double	fov = 60 * M_PI / 180;
	t_sphere		sphere = {{0, 0, -55}, 20, {1, 0, 0}};
	t_light			light = {{15, 70, -30}, 1000000};
	t_vec			p;
	t_vec			n;
	t_vec			pixel_light;
	int				color;
	double			tmp;

	ray.o = (t_vec){0, 0, 0};
	j = resolution.y;
	while (--j >= 0)
	{
		i = resolution.x;
		while (--i >= 0)
		{
			ray.direction = (t_vec) {i - resolution.x / 2, j - resolution.y / 2, - resolution.x / (2 * tan(fov / 2))};
			normalise(&ray.direction);
			if (intersection(ray, sphere, &p, &n))
			{
				tmp = scalar_product(get_normalized(vector_difference(light.o, p)), n) / get_norm2(vector_difference(light.o, p));
				if (tmp < 0)
					tmp = 0;
				pixel_light = vector_product(sphere.albedo ,light.intensity * tmp);
				color = create_trgb(0, pixel_light.x, pixel_light.y, pixel_light.z);
				my_mlx_pixel_put(data, i, resolution.y - j - 1, color);
			}

		}
	}
	return (0);
}

int	main(void)
{
	void		*mlx;
	t_data		img;
	void		*window;
	const int	height = 1024;
	const int	width = height; //* 16 / 9;

	mlx = mlx_init();
	if (!mlx)
		return (-1);
	window = mlx_new_window(mlx, width, height, "mini_rt");
	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	display_stuff((t_point){width, height}, &img);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}
