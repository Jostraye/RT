/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/20 16:56:50 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	TEXTURES CHOSER
*/

char		textures_coef(t_obj *obj, t_hit_rec *hit, t_ray ray)
{
	if (obj->type == 3 && SPHERE_TEXTURE)
		return (get_columns_sphere(hit, ray));
	else if (obj->type == 6 && PLANE_CHECKERS)
		return (checkerboard_plane(hit, ray));
	else if (obj->type == 4 && CYLINDER_TEXTURE)
		return (get_lines_cylinder(hit, ray));
	else if (obj->type == 5 && CONE_TEXTURE)
		return (get_lines_cone(hit, ray));
	else
		return (0);
}
