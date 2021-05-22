/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_rotation_x.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:13:55 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/21 22:14:07 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	rotation_x(t_vec *vec, double angle)
{
	t_vec	tmp;

	tmp.x = vec->x;
	tmp.y = vec->y * cos(angle) + vec->z * -sin(angle);
	tmp.z = vec->y * sin(angle) + vec->z * cos(angle);
	*vec = tmp;
}
