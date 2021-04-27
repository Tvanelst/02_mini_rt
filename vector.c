/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:08:42 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/27 17:47:01 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	vector_sum(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec	vector_difference(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec	vector_product(t_vec a, float b)
{
	return ((t_vec){a.x * b, a.y * b, a.z * b});
}

t_vec	vector_quotient(t_vec a, float b)
{
	return ((t_vec){a.x / b, a.y / b, a.z / b});
}

double	scalar_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	get_norm2(t_vec a)
{
	return (scalar_product(a, a));
}

void	normalise(t_vec *a)
{
	double	norm;

	norm = sqrt(get_norm2(*a));
	a->x /= norm;
	a->y /= norm;
	a->z /= norm;
}

t_vec	get_normalized(t_vec a)
{
	t_vec b;

	b = a;
	normalise(&b);
	return (b);
}
