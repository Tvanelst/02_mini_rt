/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/27 14:01:38 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <limits.h>
#include "mini_rt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	display_square(t_point point, int height, int width, t_data *data)
{
	int	i;

	while (height-- > 0)
	{
		i = width + 1;
		while (--i > 0)
			my_mlx_pixel_put(data, point.x + i, point.y + height + 1, 0x00FF0000);
	}
}

void	display_circle(t_point center, int radius, t_data *data)
{
	int		largestX;
	int		y;
	int		x;
	t_point	origin;

	largestX = radius;
	y = -1;
	while (++y <= radius)
	{
		x = largestX + 1;
		while (--x >= 0)
		{
			if ((x * x) + (y * y) <= (radius * radius))
			{
				origin = (t_point){center.x - x, center.y - y};
				display_square(origin, 1, 2 * x, data);
				origin = (t_point){center.x - x, center.y + y};
				display_square(origin, 1, 2 * x, data);
				largestX = x;
				break ;
			}
		}
	}
}

int	main(void)
{
	void		*mlx;
	t_data		img;
	void		*window;
	const int	height = 720;
	const int	width = height * 16 / 9;

	mlx = mlx_init();
	if (!mlx)
		return (-1);
	window = mlx_new_window(mlx, width, height, "Helllo world");
	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	display_square((t_point){100, 100}, 100, 100, &img);
	display_circle((t_point){800, 100}, 80, &img);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}
