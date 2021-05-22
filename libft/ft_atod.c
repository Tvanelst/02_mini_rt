/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:29:32 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/21 23:31:17 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(char *str)
{
	double	n;
	int		n_dec;
	size_t	n_dec_len;

	n = ft_atoi(str);
	str = ft_strchr(str, '.');
	if (str && *(++str))
	{
		n_dec = ft_atoi(str);
		n_dec_len = ft_strlen(str);
		n *= (10 * n_dec_len);
		if (n >= 0)
			n += n_dec;
		else
			n -= n_dec;
		n /= (10 * n_dec_len);
	}
	return (n);
}
