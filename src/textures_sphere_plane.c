/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_sphere_plane.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/17 18:16:47 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	SPHERE TEXTURES
*/

char		get_lines_sphere(t_hit_rec *hit, t_ray ray)
{
	double	v;
	t_vc	sph_pos;
	int		l;

	l = 12;
	// l parametre a intégrer dans les propriétés objets (taille texture)
	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
	v = 0.5 - asin(sph_pos.x) / M_PI;
	if ((int)(l * v) % 2)
		return (0);
	else
		return (1);
}

char		get_columns_sphere(t_hit_rec *hit, t_ray ray)
{
	double	u;
	int		l;
	t_vc	sph_pos;

	l = 12;
	// l parametre a intégrer dans les propriétés objets (taille texture)
	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
	u = 0.5 + atan2(sph_pos.z, sph_pos.y) / (2 * M_PI);
	if ((int)(l * u) % 2)
		return (0);
	else
		return (1);
}

char		get_checkerboard_sphere(t_hit_rec *hit, t_ray ray)
{
	double	u;
	double	v;
	int		l;
	t_vc	sph_pos;

	l = 8;
	// l parametre a intégrer dans les propriétés objets (taille texture)
	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
	u = 0.5 + atan2(sph_pos.z, sph_pos.y) / (2 * M_PI);
	v = 0.5 - asin(sph_pos.x) / M_PI;
	if (((int)(l * u) % 2 + (int)(l * v)) % 2)
		return (0);
	else
		return (1);
}

int			get_texture_sphere(t_hit_rec *hit, t_ray ray)
{
	double	u;
	double	v;
	int		a;
	int		b;
	t_vc	sph_pos;

	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
	u = 0.5 + atan2(sph_pos.z, sph_pos.y) / (2 * M_PI);
	v = 0.5 - asin(sph_pos.x) / M_PI;
	a = (int)(v * hit->hit_obj->texture_size[1]);
	b = (int)(u * hit->hit_obj->texture_size[0]);
	return (hit->hit_obj->texture_tab[(int)(v * hit->hit_obj->texture_size[1])][(int)(u * hit->hit_obj->texture_size[0])]);
}

/*
**	PLANE TEXTURES
*/

char		checkerboard_plane(t_hit_rec *hit, t_ray ray)
{
	t_vc	xy_pos;
	double	teta;
	int		mod;

	xy_pos = vec_sub(vec_add(vec_mult(ray.direction, hit->t),
		ray.origin), hit->hit_obj->pos);
	teta = acos(vec_dot(hit->hit_obj->rot, init_vc(0, 0, 1)));
	xy_pos = rot_x(xy_pos, (int)(teta * 180 / M_PI));
	xy_pos = rot_y(xy_pos, (int)(teta * 180 / M_PI));
	mod = (xy_pos.x * xy_pos.y > 0) ? 1 : 0;
	if (abs((int)xy_pos.x / 350 - (int)xy_pos.y / 350) % 2 == mod)
		return (0);
	else
		return (1);
}
