/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:26:36 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/03 20:56:39 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	save_bmp(t_img *img, t_scene *s)
{
	const char	tag[] = {'B', 'M'};
	const t_point	*resolution = s->resolution.ptr;
	const int	header[] = {0x3a, 0x00, 0x36,
							0x28,
        					resolution->x, resolution->y, img->bits_per_pixel,
        0x01,            // 24 bits/pixel, 1 color plane
        0,                   // BI_RGB no compression
        0,                   // Pixel data size in bytes
        0x002e23, 0x002e23,  // Print resolution
        0, 0,                // No color palette
    };
	char bitmap[] = {
        0x35, // Blue
        0x41, // Green
        0xef, // Red
        0x00  // Padding
    };
	int fd;

	fd = open("img.bmp", O_WRONLY | O_CREAT | O_APPEND);
	printf("bmp = %d", fd);
	write(fd, tag, sizeof(tag));
	write(fd, header, sizeof(header));
	write(fd, bitmap, sizeof(bitmap));
	(void)img;
	close(fd);
	return (0);
}
