/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:38:20 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/17 00:30:20 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	rotation_x(t_vec *vec, double angle)
{
	t_vec	tmp;

	tmp.x = vec->x;
	tmp.y = vec->y * cos(angle) + vec->z * -sin(angle);
	tmp.z = vec->y * sin(angle) + vec->z * cos(angle);
	*vec = tmp;
}

void	rotation_y(t_vec *vec, double angle)
{
	t_vec	tmp;

	tmp.x = vec->x * cos(angle) + vec->z * sin(angle);
	tmp.y = vec->y;
	tmp.z = vec->x * -sin(angle) + vec->z * cos(angle);
	*vec = tmp;
}

void	rotation_z(t_vec *vec, double angle)
{
	t_vec	tmp;

	tmp.x = vec->x * cos(angle) + vec->y * -sin(angle);
	tmp.y = vec->x * sin(angle) + vec->y * cos(angle);
	tmp.z = vec->z;
	*vec = tmp;
}

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
