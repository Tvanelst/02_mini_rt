/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:11:40 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/05 17:40:05 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_of_words(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

static size_t	word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	return (i);
}

static char	**ft_clear(char **ptr, size_t index)
{
	while (index--)
		free(*(ptr + index));
	free(ptr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*ptr2;
	size_t	i;
	size_t	j;

	ptr = malloc(sizeof(*ptr) * (num_of_words(s, c) + 1));
	if (!ptr)
		return (NULL);
	j = 0;
	while (*s)
	{
		if (*s++ != c)
		{
			i = 0;
			ptr2 = malloc(word_len(--s, c) + 1);
			if (!ptr2)
				return (ft_clear(ptr, j));
			while (*s && *s != c)
				*(ptr2 + i++) = *s++;
			*(ptr2 + i) = 0;
			*(ptr + j++) = ptr2;
		}
	}
	*(ptr + j) = 0;
	return (ptr);
}
