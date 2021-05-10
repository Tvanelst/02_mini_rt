/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:34:00 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/10 11:05:16 by tvanelst         ###   ########.fr       */
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
	size_t			i;

	x.d = INFINITY;
	i = -1;
	while (++i < s->spheres.size)
		if (sp_intersection(l_ray, ((t_sphere *)s->spheres.ptr)[i], &x)
		&& x.d * x.d < x2->d)
			return (1);
	return (0);
}

static double	light_power(t_scene *s, t_intersection *x)
{
	const t_light	*lights = s->lights.ptr;
	size_t			i;
	t_vec			vec_light_p;
	double			light_norm;
	double			light_power;

	light_power = 0.0;
	i = 0;
	while (i < s->lights.size)
	{
		vec_light_p = vec_d(lights[i].o, x->p);
		x->d = get_norm2(vec_light_p);
		light_norm = scalar_p(normed(vec_light_p), x->n) / x->d;
		if (light_norm < 0)
			light_norm = 0;
		if (!is_shadow(s, x, vec_light_p))
			light_power += lights[i].intensity * light_norm;
		i++;
	}
	return (light_power);
}

static t_vec	pixel_color(t_scene *s, int i[2], t_intersection *x)
{
	const t_sphere		*sp = s->spheres.ptr;
	const t_triangle	*tr = s->triangles.ptr;
	const t_plane	*pl = s->planes.ptr;
	const t_light		*amb_light = s->amb_light.ptr;
	t_vec				pixel_color;
	double				light_pow;

	light_pow = light_power(s, x);
	if (light_pow < amb_light[0].intensity)
		light_pow = amb_light[0].intensity;
	if (i[1] == sphere)
		pixel_color = vec_p(sp[i[0]].color, light_pow);
	else if (i[1] == triangle)
		pixel_color = vec_p(tr[i[0]].color, light_pow);
	else if (i[1] == plane)
		pixel_color = vec_p(pl[i[0]].color, light_pow);
	else
		return ((t_vec){0});
	return (pixel_color);
}

void	compute_pixel(t_ray ray, t_scene *s, t_point pixel, t_img *data)
{
	t_intersection	x;
	size_t			i;
	int				*closest;

	x = (t_intersection){{0, 0, 0}, {0, 0, 0}, INFINITY};
	closest = (int []){-1, 0};
	i = -1;
	while (++i < s->spheres.size)
		if (sp_intersection(ray, ((t_sphere *)s->spheres.ptr)[i], &x))
			closest = (int []){i, sphere};
	i = -1;
	while (++i < s->triangles.size)
		if (tr_intersection(ray, ((t_triangle *)s->triangles.ptr)[i], &x))
			closest = (int []){i, triangle};
	i = -1;
	while (++i < s->planes.size)
		if (pl_intersection(ray, ((t_plane *)s->planes.ptr)[i], &x))
			closest = (int []){i, plane};
	if (closest >= 0)
	{
		if (!data->bmp)
			pixel.y = ((t_point *)s->resolution.ptr)->y - pixel.y - 1;
		draw_pixel(pixel_color(s, closest, &x), data, pixel);
	}
}
