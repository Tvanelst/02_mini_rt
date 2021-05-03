/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:34:00 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/03 17:12:42 by tvanelst         ###   ########.fr       */
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

static int	is_shadow(t_scene *s, t_vec p, double d_l)
{
	t_ray	l_ray;
	t_vec	p_l;
	t_vec	vec[2];
	size_t	i;
	double	t_l;

	t_l = 1E99;
	p_l = get_norm(vec_d(((t_light *)s->lights.ptr)[0].o, p));
	l_ray = (t_ray){vec_s(p, vec_p(vec[1], 0.1)), p_l};
	i = -1;
	while (++i < s->spheres.size)
		if (intersection(l_ray, ((t_sphere *)s->spheres.ptr)[i++], vec, &t_l) &&
		t_l * t_l < d_l)
			return (1);
	return (0);
}

static t_vec	get_p_light(t_scene *s, int i, t_vec p, t_vec n)
{
	t_vec	vec_light_p;
	double	light_norm;
	double	d_l;
	t_vec	p_light;

	vec_light_p = vec_d(((t_light *)s->lights.ptr)[0].o, p);
	d_l = get_norm2(vec_light_p);
	light_norm = scalar_p(get_norm(vec_light_p), n) / get_norm2(vec_light_p);
	if (light_norm < 0)
		light_norm = 0;
	if (is_shadow(s, p, d_l))
		p_light = vec_p(((t_sphere *)s->spheres.ptr)[i].color, ((t_light *)s->amb_light.ptr)[0].intensity);
	else
		p_light = vec_p(((t_sphere *)s->spheres.ptr)[i].color,
				((t_light *)s->lights.ptr)[0].intensity * light_norm);
	return (p_light);
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
		pixel.y = ((t_point *)s->resolution.ptr)->y - pixel.y - 1;
		draw_pixel(get_p_light(s, closest, vec[0], vec[1]), data, pixel);
	}
}
