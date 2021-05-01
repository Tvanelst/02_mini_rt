/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:01:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/01 15:00:43 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	*ext_malloc(void *ptr_old, size_t size, size_t n)
{
	char	*ptr_new;

	ptr_new = malloc(size * (n + 1));
	if (!ptr_new)
		return (NULL);
	if (ptr_old)
	{
		ft_memcpy(ptr_new, ptr_old, size * n);
		free(ptr_old);
	}
	return (ptr_new);
}

int	add_sphere(t_scene *s, char **ptr)
{
	t_sphere	**spheres;
	size_t		*size;

	spheres = (t_sphere **)&s->spheres.ptr;
	size = &s->spheres.size;
	*spheres = ext_malloc(*spheres, sizeof(t_sphere), *size);
	if (!ft_atov(ptr[1], &(*spheres)[*size].c))
		return (0);
	(*spheres)[*size].r = ft_atod(ptr[2]);
	if (!ft_atov(ptr[3], &(*spheres)[*size].color))
		return (0);
	*size += 1;
	return (1);
}

int	add_square(t_scene *s, char **ptr)
{
	t_square	**squares;
	size_t		*size;

	squares = (t_square **)&s->squares.ptr;
	size = &s->squares.size;
	*squares = ext_malloc(*squares, sizeof(t_square), *size);
	if (!ft_atov(ptr[1], &(*squares)[*size].o))
		return (0);
	if (!ft_atov(ptr[2], &(*squares)[*size].orientation))
		return (0);
	(*squares)[*size].size = ft_atod(ptr[3]);
	if (!ft_atov(ptr[4], &(*squares)[*size].color))
		return (0);
	*size += 1;
	return (1);
}

int	add_resolution(t_scene *s, char **ptr)
{
	s->resolution = (t_point){ft_atoi(ptr[1]), ft_atoi(ptr[2])};
	if (s->resolution.x < 0 || s->resolution.y < 0)
		return (0);
	return (1);
}

int	process_line(t_scene *s, char *str)
{
	char	**ptr;
	t_tuple	*funptr;
	int		i;

	ptr = ft_split(str, ' ');
	if (!ptr)
		return (-1);
	funptr = (t_tuple[]){{"sp", &add_sphere}, {"sq", &add_square},
	{"R", &add_resolution}};
	i = 0;
	while (ft_strncmp(ptr[0], funptr[i].str, 3) && i <= 3)
		i++;
	if (i < 3)
	{
		if (!funptr[i].func(s, ptr))
			return (-1);
	}
	else
		return (-1);
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (0);
}

t_scene	create_scene(int fd)
{
	t_scene	scene;
	char	*line;

	scene.resolution = (t_point){-1, -1};
	scene.spheres = (t_array){0, 0};
	while (get_next_line(fd, &line))
	{
		process_line(&scene, line);
		free(line);
	}
	if (line)
	{
		process_line(&scene, line);
		free(line);
	}
	scene.cameras[0] = (t_camera){{0, 0, 0}, {0, 0, -1}, 60};
	scene.ligths[0] = (t_light){{15, 60, -10}, 1000000, {1, 0, 1}};
	return (scene);
}
