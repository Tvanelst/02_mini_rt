/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:18:59 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/22 20:42:41 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	get_malloc_size(char *buffer)
{
	size_t	i;

	i = 0;
	while (*(buffer + i) && *(buffer + i) != '\n' && i < BUFFER_SIZE)
		i++;
	return (i);
}

static int	fill_line(char *buffer, char **line, char **my_line, int *j)
{
	int	i;

	i = 0;
	while (!buffer[i] && i < BUFFER_SIZE - 1)
		i++;
	while (buffer[i])
	{
		if (buffer[i++] != '\n')
			my_line[0][(*j)++] = buffer[i - 1];
		else
		{
			buffer[i - 1] = '\0';
			my_line[0][*j] = '\0';
			*line = *my_line;
			return (1);
		}
		buffer[i - 1] = '\0';
	}
	my_line[0][*j] = '\0';
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*my_line;
	int			counters[2];

	if (!line)
		return (-1);
	counters[1] = 0;
	my_line = 0;
	while (1)
	{
		my_line = ft_extend_malloc(my_line, get_malloc_size(buffer));
		if (!my_line)
			return (-1);
		if (fill_line(buffer, line, &my_line, &counters[1]))
			return (1);
		counters[0] = read(fd, buffer, BUFFER_SIZE);
		if (counters[0] < 1)
		{
			if (counters[0] == -1)
				free(my_line);
			else
				*line = my_line;
			return (counters[0]);
		}
	}
}
