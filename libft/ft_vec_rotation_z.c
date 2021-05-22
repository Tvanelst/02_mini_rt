/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_rotation_z.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:14:31 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/21 22:14:47 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	rotation_z(t_vec *vec, double angle)
{
	t_vec	tmp;

	tmp.x = vec->x * cos(angle) + vec->y * -sin(angle);
	tmp.y = vec->x * sin(angle) + vec->y * cos(angle);
	tmp.z = vec->z;
	*vec = tmp;
}
