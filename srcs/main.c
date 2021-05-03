/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/03 20:54:07 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	get_ray_direction(t_scene *s, t_point pixel)
{
	const double	r_fov = ((t_camera *)s->cameras.ptr)[0].fov * M_PI / 180;
	t_vec			direction;

	direction.x = pixel.x - ((t_point *)s->resolution.ptr)->x / 2;
	direction.y = pixel.y - ((t_point *)s->resolution.ptr)->y / 2;
	direction.z = -((t_point *)s->resolution.ptr)->x / (2 * tan(r_fov / 2));
	normalise(&direction);
	return (direction);
}

int	create_image(t_img *img, t_scene *s)
{
	t_point			pixel;
	t_ray			ray;

	ray.o = ((t_camera *)s->cameras.ptr)[0].o;
	pixel.y = ((t_point *)s->resolution.ptr)->y;
	while (--pixel.y >= 0)
	{
		pixel.x = ((t_point *)s->resolution.ptr)->x;
		while (--pixel.x >= 0)
		{
			ray.direction = get_ray_direction(s, pixel);
			compute_pixel(ray, s, pixel, img);
		}
	}
	return (0);
}

int	validate_input(int argc, char **argv, t_scene *s)
{
	int	fd;

	if (argc < 2 || argc > 3)
		return (printf("to few or to many arguments"));
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
		return (printf("invalide second argument"));
	else if (!argv[1] || ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 4))
		return (printf("invalide first argument test"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("impossible to open the file"));
	if (!create_scene(fd, s))
		return (printf("file misformatted !"));
	close(fd);
	return (0);
}

void	key_hook_setup(void *mlx, void *window)
{
	t_vars	vars;

	vars.mlx = mlx;
	vars.win = window;
	mlx_key_hook(vars.win, &key_hook, &vars);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_img	img;
	t_scene	s;

	if (validate_input(argc, argv, &s))
		return (-1);
	mlx = mlx_init();
	if (!mlx)
		return (-1);
	img.img = mlx_new_image(mlx, ((t_point *)s.resolution.ptr)->x,
			((t_point *)s.resolution.ptr)->y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len,
			&img.endian);
	create_image(&img, &s);
	if (argc == 3)
		return (save_bmp(&img, &s));
	else
	{
		window = mlx_new_window(mlx, ((t_point *)s.resolution.ptr)->x,
				((t_point *)s.resolution.ptr)->y, "mini_rt");
		key_hook_setup(mlx, window);
		mlx_put_image_to_window(mlx, window, img.img, 0, 0);
		mlx_loop(mlx);
	}
}
