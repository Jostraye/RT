/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 14:56:12 by jostraye         ###   ########.fr       */
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
	n = vec_sub(vec_add(vec_mult(ray.direction, hit->t), x), vec_mult(obj->rot, m));
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
	n = vec_sub(vec_add(vec_mult(ray.direction, hit->t), x), vec_mult(obj->rot, (m + k)));
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
	n = vec_sub(vec_add(vec_mult(ray.direction, hit->t), x), vec_mult(obj->rot, m));
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

double		shadow_cutter(t_env *e, t_hit_rec *hit, t_obj *light_obj, t_ray ray)
{
	t_vc		inter;
	t_obj		*clst;
	t_ray		light_r;
	t_hit_rec 	hit_s;
	double		tr;

	light_r.origin = inter_position(ray, hit->t);
	light_r.direction = vec_sub(light_obj->pos, light_r.origin);
	clst = e->cut_link;
	while (clst)
	{
		if (nearest_node(e, light_r, &hit_s))
		{
			tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r))) ? hit_s.hit_obj->tr : 0;
			inter = vec_sub(vec_add(vec_mult(light_r.direction, -hit_s.t), light_r.origin), clst->pos);
			if (hit_s.t > 0.000001 && hit_s.t < 0.99999 && vec_x(inter, clst->rot) > 0)
			{
				if (tr > 0)
					return (1 - tr);
				return (0);
			}
		}
		clst = clst->next;
	}
	return (0);
}

double		shadow_no_cutter(t_env *e, t_hit_rec *hit, t_obj *light_obj, t_ray ray)
{
	t_ray		light_r;
	t_hit_rec 	hit_s;
	double		tr;

	light_r.origin = inter_position(ray, hit->t);
	light_r.direction = vec_sub(light_obj->pos, light_r.origin);
	if (nearest_node(e, light_r, &hit_s))
	{
		tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r))) ? hit_s.hit_obj->tr : 0;
		if (hit_s.t > 0.000001 && hit_s.t < 0.99999)
				return (1 - tr);
	}
	return (0);
}

double		shadows(t_env *e, t_hit_rec *hit, t_obj *light_obj, t_ray ray)
{
	t_obj *olst;

	olst = e->obj_link;
	while (olst)
	{
		if (is_not_cut(olst, e))
			return (shadow_no_cutter(e, hit, light_obj, ray));
		if (!is_not_cut(olst, e))
			return (shadow_cutter(e, hit, light_obj, ray));
		olst = olst->next;
	}
	return (0);
}
