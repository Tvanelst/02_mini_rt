/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_normalise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:11:13 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/28 18:13:25 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	normalise(t_vec *a)
{
	double	norm;

	norm = sqrt(get_norm2(*a));
	a->x /= norm;
	a->y /= norm;
	a->z /= norm;
}
