/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:19:17 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/22 18:18:46 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

static void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		my_c;
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	ptr1 = dst;
	ptr2 = src;
	my_c = c;
	while (n-- > 0)
	{
		*ptr1++ = *ptr2;
		if (*ptr2++ == my_c)
			return (ptr1);
	}
	return (0);
}

char	*ft_extend_malloc(char *s1, size_t size)
{
	size_t	size1;
	char	*ptr;

	size1 = 0;
	if (s1)
		size1 = ft_strlen(s1);
	ptr = malloc(size1 + size + 1);
	if (!ptr)
		return (NULL);
	if (s1)
	{
		ft_memccpy(ptr, s1, 0, size1);
		free(s1);
	}
	return (ptr);
}
