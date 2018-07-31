/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/13 15:09:19 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		get_minimum_tr(t_hit_rec hit_s, t_obj *olst, t_ray light_r)
{
	double	tr;
	double	t;
	double	tr_max;

	tr_max = 1;
	t = distance_to_inter(&hit_s, olst, light_r);
	if (t > 0.000001 && t < 0.999999)
	{
		hit_s.hit_obj = olst;
		hit_s.t = hit_s.t1;
		hit_s.n = normal_vectors(&hit_s, hit_s.hit_obj, light_r);
		tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r)))
			? hit_s.hit_obj->tr : 0;
		tr_max = (tr < tr_max) ? tr : tr_max;
	}
	if (hit_s.t2 > 0.000001 && hit_s.t2 < 0.999999 && tr > 0)
	{
		hit_s.t = hit_s.t2;
		hit_s.n = normal_vectors(&hit_s, hit_s.hit_obj, light_r);
		tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r)))
			? hit_s.hit_obj->tr : 0;
		tr_max = (tr < tr_max) ? tr : tr_max;
	}
	return (tr_max);
}

t_obj		*get_cutter(t_env *e, t_obj *obj)
{
	t_obj *cut;

	cut = e->cut_link;
	while (cut)
	{
		if (cut->id_cut == obj->id_obj)
			return (cut);
		cut = cut->next;
	}
	return (NULL);
}

double		get_minimum_tr_cut(t_env *e, t_hit_rec hit_s,
	t_obj *olst, t_ray light_r)
{
	double	tr;
	double	tr_max;
	t_vc	inter;
	t_obj	*cut;

	tr_max = 1;
	if (hit_cut(&hit_s, e, olst, light_r))
	{
		cut = get_cutter(e, olst);
		inter = vec_sub(vec_add(vec_mult(light_r.direction, hit_s.t),
			light_r.origin), cut->pos);
		tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r)))
			? hit_s.hit_obj->tr : 0;
		tr_max = (tr < tr_max) ? tr : tr_max;
		if (hit_s.t2 > 0.00001 && hit_s.t2 < 0.999999 && tr > 0.01)
		{
			hit_s.t = hit_s.t2;
			hit_s.n = normal_vectors(&hit_s, hit_s.hit_obj, light_r);
			tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r)))
				? hit_s.hit_obj->tr : 0;
			tr_max = (tr < tr_max) ? tr : tr_max;
		}
	}
	return (tr_max);
}

double		shadow_calculation(t_env *e, t_ray light_r)
{
	t_hit_rec	hit_s;
	double		tr_max;
	double		tr;
	t_obj		*olst;

	tr_max = 1;
	olst = e->obj_link;
	hit_s.t2 = -1;
	while (olst)
	{
		if (is_not_cut(olst, e))
		{
			tr = get_minimum_tr(hit_s, olst, light_r);
			tr_max = (tr < tr_max) ? tr : tr_max;
		}
		else
		{
			
			tr = get_minimum_tr_cut(e, hit_s, olst, light_r);

			tr_max = (tr < tr_max) ? tr : tr_max;
		}
		olst = olst->next;
	}
	return (tr_max);
}

/*
** shadows() returns:
** tr coefficient of object between intersection and light
** 0 if object is opaque
** 1 if object is transparent or no intersection between object and light
*/

double		shadows(t_env *e, t_hit_rec *hit, t_obj *light_obj, t_ray ray)
{
	t_ray	light_r;

	light_r.origin = inter_position(ray, hit->t);
	light_r.direction = vec_sub(light_obj->pos, light_r.origin);

	return (shadow_calculation(e, light_r));
}
