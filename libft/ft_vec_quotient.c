/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_quotient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:11:21 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/21 22:15:36 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

t_vec	vec_q(t_vec a, float b)
{
	return ((t_vec){a.x / b, a.y / b, a.z / b});
}
