/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:36:35 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/05 16:38:36 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "struct.h"

typedef struct s_camera
{
	t_vec	o;
	t_vec	direction;
	int		fov;
}				t_camera;

int		add_c(t_array *arr, char **ptr);
#endif