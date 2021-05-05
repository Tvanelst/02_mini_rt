/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:37:08 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/05 16:40:13 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "struct.h"

typedef struct s_light
{
	t_vec	o;
	double	intensity;
	t_vec	color;
}			t_light;

int		add_l(t_array *arr, char **ptr);
#endif