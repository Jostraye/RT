/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_rot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:51:34 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/20 17:10:55 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vc		rot_x(t_vc vc, int t)
{
	double y;
	double z;

	y = vc.y;
	z = vc.z;
	vc.y = y * cos(t * M_PI / 180) - z * sin(t * M_PI / 180);
	vc.z = y * sin(t * M_PI / 180) + z * cos(t * M_PI / 180);
	return (vc);
}

t_vc		rot_y(t_vc vc, int t)
{
	double x;
	double z;

	x = vc.x;
	z = vc.z;
	vc.x = x * cos(t * M_PI / 180) + z * sin(t * M_PI / 180);
	vc.z = -x * sin(t * M_PI / 180) + z * cos(t * M_PI / 180);
	return (vc);
}

t_vc		rot_z(t_vc vc, int t)
{
	double x;
	double y;

	x = vc.x;
	y = vc.y;
	vc.x = x * cos(t * M_PI / 180) - y * sin(t * M_PI / 180);
	vc.y = x * sin(t * M_PI / 180) + y * cos(t * M_PI / 180);
	return (vc);
}

t_vc		rot_all_axis(t_vc vc, t_vc obj)
{
	vc = rot_z(vc, obj.z);
	vc = rot_y(vc, obj.y);
	vc = rot_x(vc, obj.x);
	return (vc);
}

t_vc		rot_all_axis_inv(t_vc vc, t_vc obj)
{
	rot_x(vc, -obj.x);
	rot_y(vc, -obj.y);
	rot_z(vc, -obj.z);
	return (vc);
}
