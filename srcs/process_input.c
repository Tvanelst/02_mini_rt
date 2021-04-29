/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:01:18 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/29 18:38:41 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* static double	atod(char *str)
{
	double	n;
	//convert char* to double
}

t_sphere	add_sphere(char *arg)
{
	size_t		i;
	t_sphere	sphere;

	i = 0;
	while (ft_is_space(*arg))
		arg++;

	return (sphere);
} */

/* scene.spheres = (t_sphere[]){{{0, 0, -55}, 20, {1, 0, 0}},
	{{0, -2020, 0}, 2000, {1, 1, 1}}, {{0, 2030, 0}, 2000, {1, 1, 1}},
	{{-2020, 0, 0}, 2000, {0, 1, 0}}, {{2020, 0, 0}, 2000, {0, 0, 1}},
	{{0, 0, -2050}, 2000, {0, 1, 1}}}; */
void	process_line(t_scene *s, char *str)
{
	while (ft_is_space(*str))
		str++;
	if (*str == 'R')
	{
		s->resolution.x = ft_atoi(++str);
		while(ft_isdigit(*str) || *str == '-' || *str == '+')
			str++;
		s->resolution.y = ft_atoi(str++);
	}
}

t_scene	create_scene(int fd)
{
	t_scene	scene;
	char	*line;

	while (get_next_line(fd, &line))
	{
		proccess_line(&scene);
		free(line);
	}
	if (line)
	{
		proccess_line(&scene);
		free(line);
	}
	scene.resolution = (t_point){1024, 1024};
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
