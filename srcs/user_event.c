/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:13:15 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/14 23:22:44 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	clean_quite(t_vars *vars)
{
	/* while (vars->s->cameras.size--) */
	/* mlx_destroy_image(vars->mlx, &vars->img[0]);
	mlx_destroy_window(vars->mlx, vars->win); */
	clear_scene(vars->s);
	free(vars->img);
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	static size_t	i = 0;

	if (keycode == 53)
		clean_quite(vars);
	else if (keycode == 49 && ++i)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img[i % vars->s->cameras.size].img, 0, 0);
	return (0);
}

void	key_hook_setup(void *mlx, void *window, t_img *img, t_scene *s)
{
	static t_vars	vars;

	vars.mlx = mlx;
	vars.win = window;
	vars.img = img;
	vars.s = s;
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(window, 17, 0, clean_quite, &vars);
}
