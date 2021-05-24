/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:27:09 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/24 14:40:17 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	keep_in_range(int *a, int min, int max)
{
	*a = fmin(fmax(*a, min), max);
}

int	create_trgb(int t, int r, int g, int b)
{
	keep_in_range(&t, 0, 255);
	keep_in_range(&r, 0, 255);
	keep_in_range(&g, 0, 255);
	keep_in_range(&b, 0, 255);
	return (t << 24 | r << 16 | g << 8 | b);
}
