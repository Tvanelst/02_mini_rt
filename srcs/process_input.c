/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:01:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/01 23:12:25 by tvanelst         ###   ########.fr       */
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
			if (tab->i)
				*(double *)tab->property = ft_atod(ptr[i]);
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
	t_point	*r;

	arr->ptr = ext_malloc(arr, sizeof(*r));
	r = (t_point *)arr->ptr + arr->size;
	*r = (t_point){ft_atoi(ptr[1]), ft_atoi(ptr[2])};
	if (r->x < 0 || r->y < 0 || arr->size > 1)
		return (0);
	return (1);
}

int	add_amb_light(t_array *arr, char **ptr)
{
	t_light	*al;

	arr->ptr = ext_malloc(arr, sizeof(*al));
	al = (t_light *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&al->intensity, 1},
			{&al->color, 0}}));
}

int	add_sphere(t_array *arr, char **ptr)
{
	t_sphere	*sp;

	arr->ptr = ext_malloc(arr, sizeof(*sp));
	sp = (t_sphere *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&sp->c, 0},
			{&sp->r, 1}, {&sp->color, 0}}));
}

int	add_square(t_array *arr, char **ptr)
{
	t_square	*sq;

	arr->ptr = ext_malloc(arr, sizeof(*sq));
	sq = (t_square *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&sq->o, 0},
			{&sq->orientation, 0}, {&sq->size, 1}, {&sq->color, 0}}));
}

int	add_light(t_array *arr, char **ptr)
{
	t_light	*l;

	arr->ptr = ext_malloc(arr, sizeof(*l));
	l = (t_light *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&l->o, 0},
			{&l->intensity, 1}, {&l->color, 0}}));
}

int	add_camera(t_array *arr, char **ptr)
{
	t_camera	*c;

	arr->ptr = ext_malloc(arr, sizeof(*c));
	c = (t_camera *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&c->o, 0},
			{&c->direction, 0}, {&c->fov, 1}}));
}

int	add_plane(t_array *arr, char **ptr)
{
	t_planes	*pl;

	arr->ptr = ext_malloc(arr, sizeof(*pl));
	pl = (t_planes *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&pl->o, 0},
			{&pl->orientation, 0}, {&pl->color, 0}}));
}

int	add_cylinder(t_array *arr, char **ptr)
{
	t_cylinders	*cy;

	arr->ptr = ext_malloc(arr, sizeof(*cy));
	cy = (t_cylinders *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&cy->o, 0},
			{&cy->orientation, 0}, {&cy->diameter, 1}, {&cy->height, 1},
			{&cy->color, 0}}));
}

int	add_triangle(t_array *arr, char **ptr)
{
	t_triangles	*tr;

	arr->ptr = ext_malloc(arr, sizeof(*tr));
	tr = (t_triangles *)arr->ptr + arr->size;
	return (create_element(arr, ptr, (t_tuple2[]){{&tr->o1, 0},
			{&tr->o2, 0}, {&tr->o3, 0}, {&tr->color, 0}}));
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
	const int	size = sizeof(fptr) / sizeof(fptr[0]);

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
