/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:16:17 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/05 17:14:13 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_sp(t_array *arr, char **ptr)
{
	t_sphere	*el;

	el = (t_sphere *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_tuple2[]){{&el->c, a_to_v},
			{&el->r, a_to_d}, {&el->color, a_to_v}}));
}

int	sp_intersection(t_ray ray, t_sphere sp, t_vec vec[2], double *t)
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