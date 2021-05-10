/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:11:43 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/10 14:25:13 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_tr(t_array *arr, char **ptr)
{
	t_triangle	*el;

	el = (t_triangle *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->o1, a_to_v},
			{&el->o2, a_to_v}, {&el->o3, a_to_v}, {&el->color, a_to_v}}));
}

double	get_factor(double d[4], double detm)
{
	const double	detx = d[0] * d[1] - d[2] * d[3];

	return (detx / detm);
}

void	get_abc(double *factors, t_vec u, t_vec v, t_vec w)
{
	const double	m11 = get_norm2(u);
	const double	m12 = scalar_p(u, v);
	const double	m22 = get_norm2(v);
	const double	detm = m11 * m22 - m12 * m12;
	const double	b11 = scalar_p(w, u);
	const double	b21 = scalar_p(w, v);

	*factors = get_factor((double []){b11, m22, m12, b21}, detm);
	*(factors + 1) = get_factor((double []){m11, b21, m12, b21}, detm);
	*(factors + 2) = 1 - *factors - *(factors + 2);
}

int	tr_intersection(t_ray ray, t_triangle tr, t_intersection *x)
{
	const t_vec		n = normed(cross(vec_d(tr.o2, tr.o1),
							(vec_d(tr.o3, tr.o1))));
	const double	my_t = scalar_p(vec_d(tr.o3, ray.o), n)
							/ scalar_p(ray.direction, n);
	const t_vec		p = vec_s(ray.o, vec_p(ray.direction, my_t));
	double			factors[3];
	int				i;

	if (my_t < 0)
		return (0);
	get_abc(factors, vec_d(tr.o2, tr.o1), vec_d(tr.o3, tr.o1), vec_d(p, tr.o1));
	i = -1;
	while (++i < 3)
		if (factors[i] < 0 || 1 < factors[i])
			return (0);
	else if (my_t < x->d)
	{
		x->d = my_t;
		x->p = p;
		x->n = n;
		return (1);
	}
	return (0);
}
