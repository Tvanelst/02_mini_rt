/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:01:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/14 20:08:22 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	*ext_malloc(t_obj_creator t)
{
	char	*ptr_new;

	ptr_new = malloc(t.size * (t.arr->size + 1));
	if (!ptr_new)
		return (NULL);
	if (t.arr->ptr)
	{
		ft_memcpy(ptr_new, t.arr->ptr, t.size * t.arr->size);
		free(t.arr->ptr);
	}
	t.arr->ptr = ptr_new;
	t.arr->size += 1;
	return (ptr_new);
}

int	create_element(char **ptr, t_obj_property *tab)
{
	size_t	i;

	i = 0;
	while (ptr[++i])
	{
		if (tab->property)
		{
			if (tab->i == a_to_d)
				*(double *)tab->property = ft_atod(ptr[i]);
			else if (tab->i == a_to_i)
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
	return (1);
}

static int	process_line(t_scene *s, char *str, unsigned int i)
{
	char				**ptr;
	const t_obj_creator	fptr[] = {
	{"R", &s->resolution, sizeof(t_point), add_r},
	{"A", &s->amb_light, sizeof(t_light), add_amb_l},
	{"c", &s->cameras, sizeof(t_camera), add_c},
	{"l", &s->lights, sizeof(t_light), add_l},
	{"sp", &s->spheres, sizeof(t_sphere), add_sp},
	{"pl", &s->planes, sizeof(t_plane), add_pl},
	{"sq", &s->squares, sizeof(t_square), add_sq},
	{"cy", &s->cylinders, sizeof(t_cylinder), add_cy},
	{"tr", &s->triangles, sizeof(t_triangle), add_tr}};

	ptr = ft_split(str, ' ');
	if (!ptr)
		return (-1);
	while (ft_strncmp(ptr[0], fptr[i].str, 3) && i <= 9)
		if (++i == 9)
			return (-1);
	if (!ext_malloc(fptr[i]) || !fptr[i].func(fptr[i].arr, ptr))
		return (-1);
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (0);
}

int	create_scene(int fd, t_scene *s)
{
	char	*line;
	int		ret;
	int		error;

	*s = (t_scene){};
	ret = 0;
	while (ret > -1)
	{
		ret = get_next_line(fd, &line);
		error = process_line(s, line, 0);
		free(line);
		if (error < 0)
			return (0);
		if (!ret)
			break ;
	}
	return (1);
}

int	validate_input(int argc, char **argv, t_scene *s, void **mlx)
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
	*mlx = mlx_init();
	if (!*mlx)
		return (-1);
	return (0);
}
