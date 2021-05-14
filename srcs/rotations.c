/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:38:20 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/14 22:50:00 by tvanelst         ###   ########.fr       */
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
