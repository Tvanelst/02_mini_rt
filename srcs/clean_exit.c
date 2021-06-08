/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 10:52:11 by tvanelst          #+#    #+#             */
/*   Updated: 2021/06/08 23:36:50 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	clear_scene(t_scene *s)
{
	t_array	**ptrs;
	size_t	i;

	ptrs = (t_array *[]){&s->amb_light, &s->lights,
		&s->spheres, &s->cameras,
		&s->cylinders, &s->resolution, &s->planes};
	i = (sizeof(ptrs) / sizeof(*ptrs));
	while (i--)
	{
		if (ptrs[i]->ptr)
			free(ptrs[i]->ptr);
		ptrs[i]->ptr = 0;
	}
}

void	handle_error(char **ptr, char *str, t_scene *s)
{
	if (ptr)
		clear_split(ptr);
	if (s)
		clear_scene(s);
	ft_putendl_fd("Error", 1);
	ft_putstr_fd(str, 1);
	exit(0);
}
