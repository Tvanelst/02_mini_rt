/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:07:59 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/01 13:28:46 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H
# include <math.h>

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}			t_vec;

t_vec	vec_s(t_vec a, t_vec b);
t_vec	vec_d(t_vec a, t_vec b);
t_vec	vec_p(t_vec a, float b);
t_vec	vec_quotient(t_vec a, float b);
double	scalar_p(t_vec a, t_vec b);
double	get_norm2(t_vec a);
void	normalise(t_vec *a);
t_vec	get_norm(t_vec a);
double	ft_atod(char *str);
int		ft_atov(char *str, t_vec *vec);
#endif