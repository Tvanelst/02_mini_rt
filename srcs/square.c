/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:59 by tvanelst          #+#    #+#             */
/*   Updated: 2021/05/14 10:01:42 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	add_sq(t_array *arr, char **ptr)
{
	t_square	*el;

	el = (t_square *)arr->ptr + arr->size - 1;
	return (create_element(ptr, (t_obj_property[]){{&el->o, a_to_v},
			{&el->orientation, a_to_v}, {&el->size, a_to_d},
			{&el->color, a_to_v}}));
}

/* t_vec	calculate_rot(t_vec *c2, t_vec *c3, t_vec rot, t_vec to)
{
	const t_vec	v = cross(to, rot);
	const float	c = vec_dot(rot, to);
	const float	norm2 = get_norm2(v);
	const float	r = ((1 - c) / norm2);
	t_vec		c1;

	c1 = (t_vec){-r * (pow(v.y, 2) + pow(v.z, 2)) + 1,
		r * v.x * v.y - v.z, r * v.x * v.z + v.y};
	*c2 = (t_vec){r * v.x * v.y + v.z,
		-r * (pow(v.x, 2) + pow(v.z, 2)) + 1, r * v.y * v.x - v.x};
	*c3 = (t_vec){r * v.x * v.z - v.y, r * v.y * v.z - v.x
		 -r * (pow(v.x, 2) + pow(v.y, 2)) + 1};
	return (c1);
}

t_vec	apply_rot(t_vec pos, t_vec dir, t_vec rot)
{
	t_vec	c1;
	t_vec	c2;
	t_vec	c3;
	t_vec	prev;

	if (dir.x == 0 && dir.y < 0 && dir.z == 0)
		pos = (t_vec){pos.x, pos.y, -pos.z};
	else if (!(dir.x == 0 && dir.y != 0 && dir.z == 0))
	{
		prev = pos;
		c1 = calculate_rot(&c2, &c3, rot, dir);
		pos = (t_vec){vec_dot(c1, prev), vec_dot(c2, prev), vec_dot(c3, prev)};
	}
	return (pos);
} */

t_vec	rotation(t_vec max, t_vec angles)
{
	t_vec	r_value;

	r_value.x = max.x * (cos(angles.x) * cos(angles.y));
	r_value.x += max.y * (cos(angles.x) * sin(angles.y) * sin(angles.z)
			- sin(angles.x) * cos(angles.z));
	r_value.x += max.z * (cos(angles.x) * sin(angles.y) * cos(angles.z)
			+ sin(angles.x) * sin(angles.z));
	r_value.x *= r_value.x;
	r_value.y += max.x * (sin(angles.x) * cos(angles.y));
	r_value.y += max.y * (sin(angles.x) * sin(angles.y) * sin(angles.z)
			+ cos(angles.x) * cos(angles.z));
	r_value.y += max.z * (sin(angles.x) * sin(angles.y) * cos(angles.z)
			- cos(angles.x) * sin(angles.z));
	r_value.y *= r_value.y;
	r_value.z = max.x * -sin(angles.y) + max.y * cos(angles.y) * sin(angles.z)
		+ max.z * cos(angles.y) * cos(angles.z);
	r_value.z *= r_value.z;
	return (r_value);
}

int	sq_intersection(t_ray ray, t_square sq, t_intersection *x)
{
	t_vec			dist_max;
	t_intersection	x2;
	const float		p = sqrt(get_norm2(sq.orientation));
	const float		ay = pow(cos(sq.orientation.y / p), -1) * 180 / M_PI;
	const float		ax = pow(cos(sq.orientation.z / p), -1) * 180 / M_PI;
	const float		az = pow(cos(sq.orientation.x / p), -1) * 180 / M_PI;

	x2 = *x;
	dist_max = rotation((t_vec){sq.size / 2, sq.size / 2, sq.size / 2}, (t_vec){ax, ay, az});
	if (pl_intersection(ray, (t_plane){sq.o, sq.orientation, sq.color}, &x2)
		&& pow((x2.p.x - sq.o.x), 2) <= dist_max.x
		&& pow((x2.p.y - sq.o.y), 2) <= dist_max.y
		&& pow((x2.p.z - sq.o.z), 2) <= dist_max.z)
	{
		*x = x2;
		x->color = sq.color;
		x->object = square;
		return (1);
	}
	return (0);
}

int	all_sq_x(t_ray ray, t_array sq_array, t_intersection *x, double l_d)
{
	const t_square	*squares = sq_array.ptr;
	size_t			i;

	i = -1;
	while (++i < sq_array.size)
		if (sq_intersection(ray, squares[i], x) && x->d * x->d < l_d)
			return (1);
	return (0);
}
