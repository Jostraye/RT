/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 11:22:43 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vc	normal_cylinder(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	m;
	t_vc	n;
	t_vc	x;

	x = vec_sub(ray.origin, obj->pos);
	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
	n = vec_add(vec_mult(ray.direction, hit->t), x);
	n = vec_sub(n, vec_mult(obj->rot, m));
	return (vec_norm(n));
}

t_vc	normal_paraboloid(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	k;
	double	m;
	t_vc	n;
	t_vc	x;

	k = obj->size;
	x = vec_sub(ray.origin, obj->pos);
	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
	n = vec_add(vec_mult(ray.direction, hit->t), x);
	n = vec_sub(n, vec_mult(obj->rot, (m + k)));
	return (vec_norm(n));
}

t_vc	normal_cone(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	m;
	t_vc	n;
	t_vc	x;

	x = vec_sub(ray.origin, obj->pos);
	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
	m *= 1 + car(tan(M_PI * obj->size / 180));
	n = vec_add(vec_mult(ray.direction, hit->t), x);
	n = vec_sub(n, vec_mult(obj->rot, m));
	return (vec_norm(n));
}

t_vc	normal_vectors(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	if (obj->type == 4)
		return (normal_cylinder(hit, obj, ray));
	else if (obj->type == 5)
		return (normal_cone(hit, obj, ray));
	else if (obj->type == 6 || obj->type == 7)
		return (vec_norm(obj->rot));
	else if (obj->type == 8)
		return (normal_paraboloid(hit, obj, ray));
	else
		return (vec_norm(vec_sub(inter_position(ray, hit->t), obj->pos)));
}
