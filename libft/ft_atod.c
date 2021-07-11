/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:29:32 by tvanelst          #+#    #+#             */
/*   Updated: 2021/07/11 22:08:36 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	ft_atod(char *str)
{
	double	n;
	int		n_dec;
	size_t	n_dec_len;
	char	sign;

	sign = (*str == '-');
	n = ft_atoi(str);
	str = ft_strchr(str, '.');
	if (str && *(++str))
	{
		n_dec = ft_atoi(str);
		n_dec_len = ft_strlen(str);
		n *= pow(10, n_dec_len);
		if (n >= 0)
			n += n_dec;
		else
			n -= n_dec;
		n /= pow(10, n_dec_len);
	}
	if (sign && (-1) < n && n < 1)
		n *= -1;
	return (n);
}
