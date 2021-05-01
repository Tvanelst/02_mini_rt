/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:01:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/01 13:32:41 by tvanelst         ###   ########.fr       */
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

/* int	add_sphere(t_scene *s, char **ptr)
{
	s->cameras = ext_malloc(s->cameras, sizeof(t_sphere), s->n_c);
	if (!ft_atov(ptr[1], &s->cameras[s->n_sp].o))
		return (0);
	if (!ft_atov(ptr[2], &s->cameras[s->n_sp].direction))
		return (0);
	s->cameras[s->n_c].fov = ft_atoi(ptr[3]);
	s->n_sp += 1;
	return (1);
} */

int	process_line(t_scene *s, char *str)
{
	char	**ptr;
	int		i;

	ptr = ft_split(str, ' ');
	if (!ptr)
		return (-1);
	if (!ft_strncmp(ptr[0], "R", 2))
		s->resolution = (t_point){ft_atoi(ptr[1]), ft_atoi(ptr[2])};
	else if (!ft_strncmp(ptr[0], "sp", 3))
	{
		if (!add_sphere(s, ptr))
			return (-1);
	}
	else if (!ft_strncmp(ptr[0], "c", 2))
	{
		//malloc cameras
	}
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
