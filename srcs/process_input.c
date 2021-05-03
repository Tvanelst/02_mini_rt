/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:01:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/03 09:43:01 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	*ext_malloc(t_array *arr, size_t size)
{
	char	*ptr_new;

	ptr_new = malloc(size * (arr->size + 1));
	if (!ptr_new)
		return (NULL);
	if (arr->ptr)
	{
		ft_memcpy(ptr_new, arr->ptr, size * arr->size);
		free(arr->ptr);
	}
	return (ptr_new);
}

int	create_element(t_array *arr, char **ptr, t_tuple2 *tab)
{
	size_t	i;

	i = 0;
	while (ptr[++i])
	{
		if (tab->property)
		{
			if (tab->i == 1)
				*(double *)tab->property = ft_atod(ptr[i]);
			else if (tab->i == 2)
			{
				*(int *)tab->property = ft_atoi(ptr[i]);
				if (*(int *)tab->property < 0)
					return (0);
			}
			else
				if (!ft_atov(ptr[i], tab->property))
					return (0);
		}
		tab++;
	}
	arr->size += 1;
	return (1);
}

int	add_resolution(t_array *arr, char **ptr)
{
	t_point	*el;

	arr->ptr = ext_malloc(arr, sizeof(*el));
	el = (t_point *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&el->x, 2},
			{&el->y, 2}}));
}

int	add_amb_light(t_array *arr, char **ptr)
{
	t_light	*el;

	arr->ptr = ext_malloc(arr, sizeof(*el));
	el = (t_light *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&el->intensity, 1},
			{&el->color, 0}}));
}

int	add_sphere(t_array *arr, char **ptr)
{
	t_sphere	*el;

	arr->ptr = ext_malloc(arr, sizeof(*el));
	el = (t_sphere *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&el->c, 0},
			{&el->r, 1}, {&el->color, 0}}));
}

int	add_square(t_array *arr, char **ptr)
{
	t_square	*el;

	arr->ptr = ext_malloc(arr, sizeof(*el));
	el = (t_square *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&el->o, 0},
			{&el->orientation, 0}, {&el->size, 1}, {&el->color, 0}}));
}

int	add_light(t_array *arr, char **ptr)
{
	t_light	*el;

	arr->ptr = ext_malloc(arr, sizeof(*el));
	el = (t_light *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&el->o, 0},
			{&el->intensity, 1}, {&el->color, 0}}));
}

int	add_camera(t_array *arr, char **ptr)
{
	t_camera	*el;

	arr->ptr = ext_malloc(arr, sizeof(*el));
	el = (t_camera *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&el->o, 0},
			{&el->direction, 0}, {&el->fov, 2}}));
}

int	add_plane(t_array *arr, char **ptr)
{
	t_planes	*el;

	arr->ptr = ext_malloc(arr, sizeof(*el));
	el = (t_planes *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&el->o, 0},
			{&el->orientation, 0}, {&el->color, 0}}));
}

int	add_cylinder(t_array *arr, char **ptr)
{
	t_cylinders	*el;

	arr->ptr = ext_malloc(arr, sizeof(*el));
	el = (t_cylinders *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&el->o, 0},
			{&el->orientation, 0}, {&el->diameter, 1}, {&el->height, 1},
			{&el->color, 0}}));
}

int	add_triangle(t_array *arr, char **ptr)
{
	t_triangles	*el;

	arr->ptr = ext_malloc(arr, sizeof(*el));
	el = (t_triangles *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&el->o1, 0},
			{&el->o2, 0}, {&el->o3, 0}, {&el->color, 0}}));
}

int	process_line(t_scene *s, char *str)
{
	char			**ptr;
	unsigned int	i;
	const t_tuple	fptr[] = {{"R", &s->resolution, &add_resolution},
	{"A", &s->amb_light, &add_amb_light}, {"c", &s->cameras, &add_camera},
	{"l", &s->lights, &add_light}, {"sp", &s->spheres, &add_sphere},
	{"pl", &s->planes, &add_plane}, {"sq", &s->squares, &add_square},
	{"cy", &s->cylinders, &add_cylinder}, {"tr", &s->triangles, &add_triangle}};
	const int		size = sizeof(fptr) / sizeof(fptr[0]);

	ptr = ft_split(str, ' ');
	if (!ptr)
		return (-1);
	i = 0;
	while (ft_strncmp(ptr[0], fptr[i].str, 3) && i <= size)
		i++;
	if (i == size)
		return (-1);
	else
		if (!fptr[i].func(fptr[i].arr, ptr))
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
