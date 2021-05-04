/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:26:36 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/04 14:33:07 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	save_bmp(t_img *img, t_point *r)
{
	const int	bitmap_size = img->line_len * r->y;
	const char	*bitmap = img->addr;
	const int	header[] = {54 + bitmap_size, 0x00, 0x36, 0x28, r->x, r->y,
						0x200001, 0, 0, 0x002e23, 0x002e23, 0, 0};
	int			fd;

	fd = open("img.bmp", O_WRONLY | O_CREAT | O_APPEND, 0666);
	write(fd, "BM", 2);
	write(fd, header, sizeof(header));
	write(fd, bitmap, bitmap_size);
	(void)img;
	close(fd);
	return (0);
}
