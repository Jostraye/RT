/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 18:10:41 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			inter_sph(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	t_vc abc;
	t_vc x;

	x = vec_sub(ray.origin, obj->pos);
	abc.x = vec_squ_sum(ray.direction);
	abc.y = 2.0 * vec_x(x, ray.direction);
	abc.z = vec_squ_sum(x) - car(obj->size);
	return (quadratic_solver(hit, abc));
}

double			inter_paraboloid(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double		k;
	t_vc		v;
	t_vc		abc;
	t_vc 		x;

	x = vec_sub(ray.origin, obj->pos);
	k = obj->size;
	v = vec_norm(obj->rot);
	abc.x = vec_x(ray.direction, ray.direction) - car(vec_x(ray.direction, v));
	abc.y = 2 * (vec_x(ray.direction, x) - vec_x(ray.direction, v) * (vec_x(x, v) + 2 * k));
	abc.z = (vec_x(x, x) - vec_x(x, v) * (vec_x(x, v) + 4 * k));
	return (quadratic_solver(hit, abc));
}

double			inter_cone(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	k;
	t_vc	abc;
	t_vc 	x;

	x = vec_sub(ray.origin, obj->pos);
	k = 1 + car(tan(M_PI * obj->size / 180));
	obj->rot = vec_norm(obj->rot);
	abc.x = vec_x(ray.direction, ray.direction)
		- k * car(vec_x(ray.direction, obj->rot));
	abc.y = 2 * (vec_x(ray.direction, x)
		- k * vec_x(ray.direction, obj->rot)
		* vec_x(x, obj->rot));
	abc.z = vec_x(x, x)
		- k * car(vec_x(x, obj->rot));
	return (quadratic_solver(hit, abc));
}

double			inter_plane(t_ray ray, t_obj *obj)
{
	double 	t;
	double 	den;
	t_vc 	x;

	x = vec_sub(ray.origin, obj->pos);
	den = vec_x(ray.direction, obj->rot);
	if (den == 0)
		return (-1);
	t = -vec_x(x, obj->rot) / den;
	if (t < 0)
		return (-1);
	return (t);
}

// double			inter_disc2(t_vc ray, t_vc x, t_env *e, t_obj *obj)
// {
// 	double	t;
// 	double	d;
// 	t_vc	p;
//
// 	t = inter_plane(ray, x, obj);
// 	if (t > 0)
// 	{
// 		p = vec_sub(vec_add(vec_mult(ray, t), e->eye_lookfrom), obj->pos);
// 		d = sqrtf(vec_x(p, p));
// 		if (d <= obj->size)
// 			return (t);
// 	}
// 	return (-1.0);
// }

double			inter_cyl(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	t_vc abc;
	t_vc x;

	x = vec_sub(ray.origin, obj->pos);
	obj->rot = vec_norm(obj->rot);
	abc.x = vec_squ_sum(ray.direction) - car(vec_x(ray.direction, obj->rot));
	abc.y = 2 * (vec_x(ray.direction, x)
		- vec_x(ray.direction, obj->rot) * vec_x(x, obj->rot));
	abc.z = vec_squ_sum(x)
		- car(vec_x(x, obj->rot)) - car(obj->size);
	return (quadratic_solver(hit, abc));
}

double			t_calculator(double a, double b)
{
	if (a < 0.0000001)
	{
		if (b > 0.0000001)
			return (b);
		return (-1);
	}
	if (b < 0.0000001)
	{
		if (a > 0.0000001)
			return (a);
		return (-1);
	}
	if (a < b)
		return (a);
	return (b);
}

double			quadratic_solver(t_hit_rec *hit, t_vc abc)
{
	double d;
	double t1;
	double t2;

	d = (double)car(abc.y) - (double)(4.0 * (abc.x * abc.z));
	if (d < 0)
		return (-1);
	t1 = (-abc.y + sqrt(d)) / (2.0 * abc.x);
	t2 = (-abc.y - sqrt(d)) / (2.0 * abc.x);
	hit->t1 = (t1 < t2) ? t1 : t2;
	hit->t2 = (t1 < t2) ? t2 : t1;
	return (t_calculator(t1, t2));
}
