/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atov.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:30:20 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/24 14:58:05 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"
#include "libft.h"

int	ft_atov(char *str, t_vec *vec)
{
	char	**ptr;
	int		i;

	ptr = ft_split(str, ',');
	if (!ptr || !ptr[0]|| !ptr[1]|| !ptr[2])
		return (0);
	vec->x = ft_atod(ptr[0]);
	vec->y = ft_atod(ptr[1]);
	vec->z = ft_atod(ptr[2]);
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (1);
}
