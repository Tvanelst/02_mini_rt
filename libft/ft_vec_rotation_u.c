/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_rotation_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:13:37 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/21 22:14:52 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	rotation_u(t_vec *vec, double angle, t_vec u)
{
	t_vec			tmp;
	const double	c = cos(angle);
	const double	s = sin(angle);

	tmp.x = vec->x * (pow(u.x, 2) * (1 - c) + c);
	tmp.x += vec->y * (u.x * u.y * (1 - c) - u.z * s);
	tmp.x += vec->z * (u.x * u.z * (1 - c) + u.y * s);
	tmp.y = vec->x * (u.x * u.y * (1 - c) + u.z * s);
	tmp.y += vec->y * (pow(u.y, 2) * (1 - c) + c);
	tmp.y += vec->z * (u.y * u.z * (1 - c) - u.x * s);
	tmp.z = vec->x * (u.x * u.z * (1 - c) - u.y * s);
	tmp.z += vec->y * (u.y * u.z * (1 - c) + u.x * s);
	tmp.z += vec->z * (pow(u.z, 2) * (1 - c) + c);
	*vec = tmp;
}
