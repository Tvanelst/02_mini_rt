/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:34:00 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/05 16:18:18 by tvanelst         ###   ########.fr       */
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
		if (sp_intersection(l_ray, ((t_sphere *)s->spheres.ptr)[i++], vec, &t_l)
		&& t_l * t_l < d_l)
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
	light_norm = scalar_p(get_norm(vec_light_p), n) / d_l;
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
	int		tr;

	closest = -1;
	t = 1E99;
	i = -1;
	tr = 0;
	while (++i < s->spheres.size)
		if (sp_intersection(ray, ((t_sphere *)s->spheres.ptr)[i], vec, &t))
			closest = i;
	i = -1;
	while (++i < s->triangles.size)
		if (tr_intersection(ray, ((t_triangle *)s->triangles.ptr)[i], vec, &t))
			tr = 1;
	if (closest >= 0)
	{
		if (!data->bmp)
			pixel.y = ((t_point *)s->resolution.ptr)->y - pixel.y - 1;
		if (!tr)
			draw_pixel(get_p_light(s, closest, vec[0], vec[1]), data, pixel);
		else
			draw_pixel((t_vec){0, 0, 0}, data, pixel);
	}
}
