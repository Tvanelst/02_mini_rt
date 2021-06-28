/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:34:00 by tvanelst          #+#    #+#             */
/*   Updated: 2021/06/28 16:13:46 by tvanelst         ###   ########.fr       */
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

static int	is_shadow(t_scene *s, t_intersection *x2, t_vec l_direction)
{
	const t_vec		l_ray_position = vec_s(x2->p, vec_p(x2->n, 0.01));
	const t_vec		l_ray_direction = normed(l_direction);
	const t_ray		l_ray = {l_ray_position, l_ray_direction};
	t_intersection	x;

	x.d = INFINITY;
	if (all_sp_x(l_ray, s->spheres, &x, x2->d))
		return (1);
	if (all_pl_x(l_ray, s->planes, &x, x2->d))
		return (1);
	if (all_cy_x(l_ray, s->cylinders, &x, x2->d))
		return (1);
	return (0);
}

static t_vec	light_power(t_scene *s, t_intersection *x)
{
	const t_light	*l = s->lights.ptr;
	size_t			i;
	t_vec			vec_light_p;
	double			light_norm;
	t_vec			light_power;

	light_power = (t_vec){0};
	i = -1;
	while (++i < s->lights.size)
	{
		vec_light_p = vec_d(l[i].o, x->p);
		x->d = get_norm2(vec_light_p);
		light_norm = vec_dot(normed(vec_light_p), x->n) / x->d;
		if (x->object == sphere || x->object == cylinder)
			light_norm = fmax(light_norm, 0);
		else
			light_norm = fabs(light_norm);
		if (!is_shadow(s, x, vec_light_p))
			light_power = vec_s(light_power,
					vec_p(l[i].color, l[i].intensity * 3000 * light_norm));
	}
	return (light_power);
}

static t_vec	pixel_color(t_scene *s, t_intersection *x)
{
	const t_light	*a_l = s->amb_light.ptr;
	const t_vec		amb_l_v = vec_p(a_l->color, a_l->intensity);
	t_vec			color;

	color = vec_p_vec(vec_q(x->color, 255), vec_s(light_power(s, x), amb_l_v));
	return (color);
}

void	compute_pixel(t_ray ray, t_scene *s, t_point pixel, t_img *data)
{
	t_intersection	x;
	size_t			i;
	const t_plane	*planes = s->planes.ptr;

	x = (t_intersection){{}, {}, INFINITY, {}, none};
	i = -1;
	while (++i < s->planes.size)
	{
		if (vec_dot(planes[i].orientation, vec_d(planes[i].o, ((t_camera *)s->cameras.ptr)[0].direction)))
			pl_intersection(ray, planes[i], &x);
	}
	i = -1;
	while (++i < s->spheres.size)
		sp_intersection(ray, ((t_sphere *)s->spheres.ptr)[i], &x);
	i = -1;
	while (++i < s->cylinders.size)
		cy_intersection(ray, ((t_cylinder *)s->cylinders.ptr)[i], &x);
	if (x.object)
	{
		pixel.y = ((t_point *)s->resolution.ptr)->y - pixel.y - 1;
		draw_pixel(pixel_color(s, &x), data, pixel);
	}
}
