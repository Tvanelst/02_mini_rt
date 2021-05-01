/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:34:00 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/01 15:35:16 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	draw_pixel(t_vec pixel_light, t_img *data, t_point pixel)
{
	int		color;
	char	*dst;
	size_t	offset;

	offset = (pixel.y * data->line_len + pixel.x * (data->bits_per_pixel / 8));
	color = create_trgb(0, pixel_light.x, pixel_light.y, pixel_light.z);
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

static t_vec	get_p_light(t_scene *s, int i, t_vec p, t_vec n)
{
	t_vec	vec_light_p;
	double	light_norm;
	t_vec	p_light;

	vec_light_p = vec_d(((t_light *)s->ligths.ptr)[0].o, p);
	light_norm = scalar_p(get_norm(vec_light_p), n) / get_norm2(vec_light_p);
	if (light_norm < 0)
		light_norm = 0;
	p_light = vec_p(((t_sphere *)s->spheres.ptr)[i].color,
			((t_light *)s->ligths.ptr)[0].intensity * light_norm);
	return (p_light);
}

static int	intersection(t_ray ray, t_sphere sp, t_vec vec[2], double *t)
{
	const double	b = 2 * scalar_p(ray.direction, vec_d(ray.o, sp.c));
	const double	c = get_norm2(vec_d(ray.o, sp.c)) - sp.r * sp.r;
	const double	delta = sqrt(b * b - 4 * c);
	const double	t2 = (-b + delta) / 2;
	double			my_t;

	if (delta < 0 || t2 < 0)
		return (0);
	my_t = (-b - delta) / 2;
	if (my_t <= 0)
		my_t = t2;
	if (my_t < *t)
	{
		*t = my_t;
		*vec = vec_s(ray.o, vec_p(ray.direction, *t));
		*(vec + 1) = get_norm(vec_d(*vec, sp.c));
		return (1);
	}
	return (0);
}

void	compute_pixel(t_ray ray, t_scene *s, t_point pixel, t_img *data)
{
	t_vec	vec[2];
	double	t;
	size_t	i;
	int		closest;

	closest = -1;
	t = 1E99;
	i = -1;
	while (++i < s->spheres.size)
		if (intersection(ray, ((t_sphere *)s->spheres.ptr)[i], vec, &t))
			closest = i;
	if (closest >= 0)
	{
		pixel.y = s->resolution.y - pixel.y - 1;
		draw_pixel(get_p_light(s, closest, vec[0], vec[1]), data, pixel);
	}
}
