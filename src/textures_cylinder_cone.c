/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_cylinder_cone.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/17 18:16:47 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	CYLINDER TEXTURES
*/

char		get_lines_cylinder(t_hit_rec *hit, t_ray ray)
{
	int		mod;
	int		l;
	double	p;
	double	x;
	t_vc	inter;

	l = 200;
	// l parametre a intégrer dans les propriétés objets (taille texture)
	inter = inter_position(ray, hit->t);
	p = vec_mod(vec_sub(vec_sub(inter, vec_mult(hit->n, hit->hit_obj->size)),
		hit->hit_obj->pos));
	x = vec_x(vec_norm(inter), vec_norm(hit->hit_obj->rot));
	mod = (x < 0) ? 0 : 1;
	if ((int)(mod + p / l) % 2)
		return (0);
	else
		return (1);
}

/*
**	CONE TEXTURES
*/

char		get_lines_cone(t_hit_rec *hit, t_ray ray)
{
	int		mod;
	int		l;
	double	p;
	double	x;
	double	r;
	t_vc	inter;

	l = 100;
	// l parametre a intégrer dans les propriétés objets (taille texture)
	inter = inter_position(ray, hit->t);
	r = vec_mod(vec_sub(inter, hit->hit_obj->pos)) * sin(hit->hit_obj->size);
	p = vec_mod(vec_sub(vec_sub(inter, vec_mult(hit->n, r)),
		hit->hit_obj->pos));
	x = vec_x(vec_norm(inter), vec_norm(hit->hit_obj->rot));
	mod = (x < 0) ? 0 : 1;
	if ((int)(mod + p / l) % 2)
		return (0);
	else
		return (1);
}
