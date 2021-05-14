/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:13:15 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/14 19:41:57 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	key_hook(int keycode, t_vars *vars)
{
	static size_t	i = 0;

	(void)vars;
	if (keycode == 53)
		exit(0);
	else if (keycode == 49 && ++i)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img[i % vars->max_view].img, 0, 0);
	return (0);
}

static int	red_cross()
{
	exit(0);
	return (0);
}

void	key_hook_setup(void *mlx, void *window, t_img *img, size_t max_view)
{
	static t_vars	vars;

	vars.mlx = mlx;
	vars.win = window;
	vars.img = img;
	vars.max_view = max_view;
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(window, 17, 0, red_cross, &vars);
}
