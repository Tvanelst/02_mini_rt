/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_rotation_y.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:14:10 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/21 22:14:29 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	rotation_y(t_vec *vec, double angle)
{
	t_vec	tmp;

	tmp.x = vec->x * cos(angle) + vec->z * sin(angle);
	tmp.y = vec->y;
	tmp.z = vec->x * -sin(angle) + vec->z * cos(angle);
	*vec = tmp;
}
