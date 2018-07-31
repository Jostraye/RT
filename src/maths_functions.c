/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 18:40:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/20 17:19:06 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	car(double a)
{
	return (a * a);
}

double	vec_x(t_vc v1, t_vc v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	vec_mod(t_vc v)
{
	return (sqrt(vec_x(v, v)));
}

t_vc	vec_mult(t_vc v, double a)
{
	t_vc ret;

	ret.x = v.x * a;
	ret.y = v.y * a;
	ret.z = v.z * a;
	return (ret);
}
