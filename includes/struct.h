/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:31:28 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/05 18:18:19 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "../libft/ft_vec.h"

typedef struct s_vars {
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	char		bmp;
}				t_img;

typedef struct s_array
{
	void	*ptr;
	size_t	size;
}			t_array;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_ray
{
	t_vec	o;
	t_vec	direction;
}			t_ray;

typedef struct s_intersection
{
	t_vec	p;
	t_vec	n;
	double	d;
}				t_intersection;
#endif