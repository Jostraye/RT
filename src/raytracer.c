/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 13:55:25 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		create_ray(int y, int z, t_vc eye_rot, t_vc ray_origin)
{
	t_ray ray;

	ray.direction.x = (double)(FOV);
	ray.direction.y = (double)(WINY / 2 - y);
	ray.direction.z = (double)(WINZ / 2 - z);
	ray.direction = rot_all_axis(ray.direction, eye_rot);
	ray.origin = ray_origin;
	return (ray);
}

int			specular_diffuse(t_obj *light, t_hit_rec *hit)
{
	int		color_diff;
	int		color_spec;
	double	dot_spec;
	double	dot_diff;
	t_vc	rm;

	rm = vec_norm(vec_sub(vec_mult(hit->n, 2 * hit->cost), hit->lm));
	dot_spec = ratio_limits(pow(vec_dot(rm, vec_norm(vec_mult(hit->v, -1.0))),
		ALPHA_SPEC));
	dot_diff = ratio_limits(hit->cost);
	color_spec = multiply_color(light->col, dot_spec * hit->hit_obj->coef.x);
	color_diff = multiply_color(hit->hit_obj->col, dot_diff * hit->hit_obj->coef.y);
	color_spec = add_color(color_spec, color_diff);
	return (color_spec);
}

double		distance_to_inter(t_hit_rec *hit, t_obj *obj_list, t_ray ray)
{
	double d;

	d = -1.0;
	d = (obj_list->type == 3) ? inter_sph(hit, obj_list, ray) : d;
	d = (obj_list->type == 4) ? inter_cyl(hit, obj_list, ray) : d;
	d = (obj_list->type == 5) ? inter_cone(hit, obj_list, ray) : d;
	d = (obj_list->type == 6) ? inter_plane(ray, obj_list) : d;
	d = (obj_list->type == 8) ? inter_paraboloid(hit, obj_list, ray) : d;
	return (d);
}

int		is_not_cut(t_obj *obj, t_env *e)
{
	t_obj *cut;

	cut = e->cut_link;
	while (cut)
	{
		if (cut->id_cut == obj->id_obj)
			return (0);
		cut = cut->next;
	}
	return (1);
}

char	hit_not_cut(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	t;
	char	hit_anything;

	hit_anything = 0;
	t = distance_to_inter(hit, obj, ray);
	if (t > 0.000001 && t < hit->t)
	{
		hit->t = t;
		hit->hit_obj = obj;
		hit_anything = 1;
	}
	return (hit_anything);
}

char	hit_cut(t_hit_rec *hit, t_env *e, t_obj *obj, t_ray ray)
{
	t_obj	*clst;
	double	t;
	double	t_cut;
	t_vc	inter;
	char	hit_anything;

	hit_anything = 0;
	clst = get_cutter(e, obj);
	t_cut = distance_to_inter(hit, clst, ray);
	t = distance_to_inter(hit, obj, ray);
	inter = vec_sub(vec_add(vec_mult(ray.direction, t), ray.origin), clst->pos);
	if (t > 0.001 && t < hit->t && vec_x(inter, clst->rot) > 0.001)
	{
		hit->t = t;
		hit->hit_obj = obj;
		hit_anything = 1;
	}
	else if (t > 0.0001 && t_cut < hit->t && hit->t1 < t_cut && hit->t2 > t_cut && t_cut > 0.0001)
	{
		hit->t = t_cut;
		hit->hit_obj = clst;
		hit_anything = 1;
	}
	return (hit_anything);
}

char		nearest_node(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*olst;
	t_obj	*llst;
	char	hit_anything;

	hit_anything = 0;
	hit->hit_obj = NULL;
	hit->t = INFINITY;
	hit->t1 = -1;
	hit->t2 = -1;
	olst = e->obj_link;
	llst = e->light_link;
	while (olst)
	{
		if (is_not_cut(olst, e))
		{
			if (hit_not_cut(hit, olst, ray))
				hit_anything = 1;
		}
		else
		{
			if (hit_cut(hit, e, olst, ray))
				hit_anything = 1;
		}
		olst = olst->next;
	}
	// while (llst)
	// {
	// 		if (hit_not_cut(hit, e, llst, ray))
	// 			hit_anything = 1;
	// 	llst = llst->next;
	// }
	return (hit_anything);
}

int		phong_lighting(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*llst;
	int		color;
	double	s;

	llst = e->light_link;
	hit->n = normal_vectors(hit, hit->hit_obj, ray);
	hit->v = inter_position(ray, hit->t);
	color = multiply_color(hit->hit_obj->col, hit->hit_obj->coef.z);
	while (llst)
	{
		s = shadows(e, hit, llst, ray);
		hit->lm = vec_norm(vec_sub(llst->pos, hit->v));
		hit->cost = vec_dot(hit->n, hit->lm);
		color = add_color(multiply_color(specular_diffuse(llst, hit), s), color);
		llst = llst->next;
	}
	if (!(textures_coef(hit->hit_obj, hit, ray)))
		color = multiply_color(color, 0.6);
	return (color);
}

int		recursive_reflection(t_env *e, int old_color, t_ray ray, t_hit_rec *hit);
int		compute_point(t_env *e, t_hit_rec *hit, t_ray ray);

int		transparency(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	t_hit_rec 	next_hit;
	double		r;

	r = (!(textures_coef(hit->hit_obj, hit, ray))) ? hit->hit_obj->tr : 0;
	hit->nt--;
	next_hit = *hit;
	r_ray.direction = ray.direction;
	r_ray.origin = inter_position(ray, hit->t);
	r_ray.origin = vec_add(r_ray.origin, vec_mult(ray.direction, SHADOW_BIAS));
	if (nearest_node(e, r_ray, &next_hit))
	{
		new_color = compute_point(e, &next_hit, r_ray);
		new_color = add_color(multiply_color(new_color, r), multiply_color(old_color, (1 - r)));
		return (new_color);
	}
	return (multiply_color(old_color, (1 - r)));
}

int		recursive_reflection(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	t_hit_rec 	next_hit;
	double		r;

	hit->nr--;
	next_hit = *hit;
	r = hit->hit_obj->r;
	r_ray.direction = vec_mult(vec_norm(ray.direction), -1);
	r_ray.direction = vec_sub(vec_mult(hit->n, 2 * vec_dot(r_ray.direction, hit->n)), r_ray.direction);
	r_ray.origin = hit->hit_inter;
	if (nearest_node(e, r_ray, &next_hit))
	{
		new_color = compute_point(e, &next_hit, r_ray);
		new_color = add_color(multiply_color(new_color, r), multiply_color(old_color, (1 - r)));
		return (new_color);
	}
	return (multiply_color(old_color, (1 - r)));
}

int		compute_point(t_env *e, t_hit_rec *hit, t_ray ray)
{
	int	pixel;

	hit->nr = 1;
	hit->nt = 1;
	hit->hit_inter = inter_position(ray, hit->t);
	pixel = phong_lighting(e, ray, hit);
	if (hit->hit_obj->tr > 0 && hit->nt > 0)
		pixel = transparency(e, pixel, ray, hit);
	if (hit->hit_obj->r > 0.01 && hit->nr > 0)
		pixel = recursive_reflection(e, pixel, ray, hit);
	return (pixel);
}

// t_vclist	*compute_lights(t_env *e, t_hit_rec *hit_rec, t_ray ray)
// {
// 	t_vclist	*b_lights;
//
// }

void	*scene_plot(void *arg)
{
	t_env		*e;
	int			px_color;
	t_ray		ray;
	t_hit_rec	hit_rec;

	e = (t_env *)arg;
	e->z = (e->thread_int) * WINZ / TH_NB - 1;
	while (++(e->z) < ((e->thread_int + 1) * WINZ) / TH_NB)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			ray = create_ray(e->y, e->z, e->eye_rot, e->eye_lookfrom);
			if (nearest_node(e, ray, &hit_rec))
			{
				// if (hit_rec->type == 1)
				// 	vclist_add()
				// else
					px_color = compute_point(e, &hit_rec, ray);
					draw_point(e, e->y, e->z, px_color);
			}
		}
	}
	// blinding_lights(e);
	// stereoscopic(e);
	return (NULL);
}
