/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:13:15 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/29 13:19:41 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	if (keycode == 53)
		exit(0);
	printf("Hello from key_hook! = %d\n", keycode);
	return (0);
}
