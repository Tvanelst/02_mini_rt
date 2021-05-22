/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:07:59 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/21 22:15:49 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H
# include <math.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}			t_vec;

t_vec	vec_s(t_vec a, t_vec b);
t_vec	vec_d(t_vec a, t_vec b);
t_vec	vec_p(t_vec a, float b);
t_vec	vec_q(t_vec a, float b);
double	vec_dot(t_vec a, t_vec b);
double	get_norm2(t_vec a);
void	normalise(t_vec *a);
t_vec	normed(t_vec a);

int		ft_atov(char *str, t_vec *vec);
t_vec	cross(t_vec a, t_vec b);
t_vec	vec_p_vec(t_vec a, t_vec b);
void	rotation_x(t_vec *vec, double angle);
void	rotation_y(t_vec *vec, double angle);
void	rotation_z(t_vec *vec, double angle);
void	rotation_u(t_vec *vec, double angle, t_vec u);
#endif