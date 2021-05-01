/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:01:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/01 16:10:17 by tvanelst         ###   ########.fr       */
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

int	add_light(t_scene *s, char **ptr)
{
	t_light	**lights;
	size_t	*size;

	lights = (t_light **)&s->ligths.ptr;
	size = &s->ligths.size;
	*lights = ext_malloc(*lights, sizeof(t_light), *size);
	if (!ft_atov(ptr[1], &(*lights)[*size].o))
		return (0);
	(*lights)[*size].intensity = ft_atod(ptr[2]);
	if (!ft_atov(ptr[3], &(*lights)[*size].color))
		return (0);
	*size += 1;
	return (1);
}

int	add_amb_light(t_scene *s, char **ptr)
{
	s->amb_light.o = (t_vec){0, 0, 0};
	s->amb_light.intensity = ft_atod(ptr[1]);
	if (!ft_atov(ptr[2], &s->amb_light.color))
		return (0);
	return (1);
}

int	add_camera(t_scene *s, char **ptr)
{
	t_camera	**cameras;
	size_t		*size;

	cameras = (t_camera **)&s->cameras.ptr;
	size = &s->cameras.size;
	*cameras = ext_malloc(*cameras, sizeof(t_camera), *size);
	if (!ft_atov(ptr[1], &(*cameras)[*size].o))
		return (0);
	if (!ft_atov(ptr[2], &(*cameras)[*size].direction))
		return (0);
	(*cameras)[*size].fov = ft_atod(ptr[3]);
	*size += 1;
	return (1);
}

int	add_plane(t_scene *s, char **ptr)
{
	(void)s;
	(void)ptr;
	return (1);
}

int	add_cylinder(t_scene *s, char **ptr)
{
	(void)s;
	(void)ptr;
	return (1);
}

int	add_triangle(t_scene *s, char **ptr)
{
	(void)s;
	(void)ptr;
	return (1);
}

int	process_line(t_scene *s, char *str)
{
	char			**ptr;
	int				i;
	const t_tuple	funptr[] = {{"R", &add_resolution}, {"A", &add_amb_light},
	{"c", &add_camera}, {"l", &add_light}, {"sp", &add_sphere},
	{"pl", &add_plane}, {"sq", &add_square}, {"cy", &add_cylinder},
	{"tr", &add_triangle}};

	ptr = ft_split(str, ' ');
	if (!ptr)
		return (-1);
	i = 0;
	while (ft_strncmp(ptr[0], funptr[i].str, 3) && i <= 9)
		i++;
	if (i == 9)
		return (-1);
	else
		if (!funptr[i].func(s, ptr))
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

	scene = (t_scene){};
	scene.resolution = (t_point){-1, -1};
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
	return (scene);
}
