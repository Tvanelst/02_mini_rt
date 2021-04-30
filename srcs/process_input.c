/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:01:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/30 17:10:27 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	atod(char *str)
{
	double	n;
	int		n_dec;
	size_t	n_dec_len;

	n = ft_atoi(str);
	str = ft_strchr(str, '.');
	if (str)
	{
		n_dec = ft_atoi(str);
		n_dec_len = ft_strlen(str);
		n *= 10 * n_dec_len;
		n += n_dec;
		n /= n_dec_len;
	}
}

/* scene.spheres = (t_sphere[]){{{0, 0, -55}, 20, {1, 0, 0}},
	{{0, -2020, 0}, 2000, {1, 1, 1}}, {{0, 2030, 0}, 2000, {1, 1, 1}},
	{{-2020, 0, 0}, 2000, {0, 1, 0}}, {{2020, 0, 0}, 2000, {0, 0, 1}},
	{{0, 0, -2050}, 2000, {0, 1, 1}}}; */

static int	ft_atov(char *str, t_vec *vec)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = ft_split(str, ',');
	if (!ptr)
		return (0);
	vec->x = ft_atod(ptr[0]);
	vec->y = ft_atod(ptr[1]);
	vec->z = ft_atod(ptr[2]);
	while (*ptr)
		free((*ptr)++);
	free(ptr);
}

void	process_line(t_scene *s, char *str)
{
	char	**ptr;

	ptr = ft_split(str, ' ');
	if (!ptr)
		return (-1);
	if (!ft_strncmp(ptr[0], "R", 2))
		s->resolution = (t_point){ft_atoi(ptr[1]), ft_atoi(ptr[2])};
	else if (!ft_strncmp(ptr[0], "sp", 3))
	{
		//malloc sphere
		if (!ft_atov(ptr[1], &s->spheres[s->n_sphere].c))
			return (-1);
		s->spheres[s->n_sphere].r = ft_atod(ptr[2])
		//ft_atov(ptr[3])};
		s->n_sphere += 1;

	}
	else if (!ft_strncmp(ptr[0], "pl", 3))
	{
		//add_pl
	}
	while (*ptr)
		free((*ptr)++);
	free(ptr);
}

t_scene	create_scene(int fd)
{
	t_scene	scene;
	char	*line;

	scene.resolution = (t_point){-1, -1};
	scene.n_sphere = 0;
	while (get_next_line(fd, &line))
	{
		printf("loopline |%s|\n", line);
		process_line(&scene, line);
		free(line);
	}
	if (line)
	{
		printf("endline |%s|\n", line);
		process_line(&scene, line);
		free(line);
	}
	scene.cameras[0] = (t_camera){{0, 0, 0}, {0, 0, -1}, 60};
	scene.ligths[0] = (t_light){{15, 60, -10}, 1000000, {1, 0, 1}};
	scene.spheres[0] = (t_sphere){{0, 0, -55}, 20, {1, 0, 0}};
	scene.spheres[1] = (t_sphere){{0, -2020, 0}, 2000, {1, 1, 1}};
	scene.spheres[2] = (t_sphere){{0, 2030, 0}, 2000, {1, 1, 1}};
	scene.spheres[3] = (t_sphere){{-2020, 0, 0}, 2000, {0, 1, 0}};
	scene.spheres[4] = (t_sphere){{2020, 0, 0}, 2000, {0, 0, 1}};
	scene.spheres[5] = (t_sphere){{0, 0, -2050}, 2000, {0, 1, 1}};
	return (scene);
}
