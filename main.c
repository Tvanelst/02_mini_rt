/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/27 17:17:25 by tvanelst         ###   ########.fr       */
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

int	intersection(t_ray ray, t_sphere sphere)
{
	const double	b = 2 * scalar_product(ray.direction, vector_difference(ray.o, sphere.o));
	const double	c = get_norm2(vector_difference(ray.o, sphere.o)) - sphere.radius * sphere.radius;
	const double	delta = b * b - 4 * c;
	const double	t2 = (-b + sqrt(delta)) / 2;

	if (delta < 0)
		return (0);
	else
		return (t2 > 0);
}

int	display_stuff(t_point resolution, t_data *data)
{
	int				i;
	int				j;
	t_ray			ray;
	const double	fov = 60 * M_PI / 180;
	t_sphere		sphere = (t_sphere){(t_vec){0, 0, -55}, 20};

	ray.o = (t_vec){0, 0, 0};
	j = resolution.y;
	while (--j >= 0)
	{
		i = resolution.x;
		while (--i >= 0)
		{
			ray.direction = (t_vec) {j - resolution.x / 2, i - resolution.y / 2, - resolution.x / (2 * tan(fov / 2))};
			normalise(&ray.direction);
			if (intersection(ray, sphere))
				my_mlx_pixel_put(data, i, j, 0x00FFFFFF);
		}
	}
	return (0);
}

int	main(void)
{
	void		*mlx;
	t_data		img;
	void		*window;
	const int	height = 720;
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
