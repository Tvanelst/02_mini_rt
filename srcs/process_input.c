/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:01:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/30 18:41:48 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	ft_atod(char *str)
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
		n *= (10 * n_dec_len);
		if (n >= 0)
			n += n_dec;
		else
			n-= n_dec;
		n /= (10 * n_dec_len);
	}
	return (n);
}

/* scene.spheres = (t_sphere[]){{{0, 0, -55}, 20, {1, 0, 0}},
	{{0, -2020, 0}, 2000, {1, 1, 1}}, {{0, 2030, 0}, 2000, {1, 1, 1}},
	{{-2020, 0, 0}, 2000, {0, 1, 0}}, {{2020, 0, 0}, 2000, {0, 0, 1}},
	{{0, 0, -2050}, 2000, {0, 1, 1}}}; */

static int	ft_atov(char *str, t_vec *vec)
{
	char	**ptr;
	int		i;

	ptr = ft_split(str, ',');
	if (!ptr)
		return (0);
	vec->x = ft_atod(ptr[0]);
	vec->y = ft_atod(ptr[1]);
	vec->z = ft_atod(ptr[2]);
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return(1);
}

int	process_line(t_scene *s, char *str)
{
	char	**ptr;
	int	i;

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
		s->spheres[s->n_sphere].r = ft_atod(ptr[2]);
		if (!ft_atov(ptr[3], &s->spheres[s->n_sphere].color))
			return (-1);
		s->n_sphere += 1;
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
	printf("sphere 0 = %f,%f,%f   %f   %f,%f,%f", scene.spheres[0].c.x, scene.spheres[0].c.y, scene.spheres[0].c.z, scene.spheres[0].r, scene.spheres[0].color.x, scene.spheres[0].color.y, scene.spheres[0].color.z);
	scene.cameras[0] = (t_camera){{0, 0, 0}, {0, 0, -1}, 60};
	scene.ligths[0] = (t_light){{15, 60, -10}, 1000000, {1, 0, 1}};
	return (scene);
}
