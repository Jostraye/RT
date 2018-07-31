/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blind_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:54:34 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/24 18:10:24 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	nearest_light(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*olst;
	char	hit_anything;

	hit_anything = 0;
	hit->hit_obj = NULL;
	hit->t = INFINITY;
	hit->t1 = -1;
	hit->t2 = -1;
	olst = e->light_link;
	while (olst)
	{
		if (is_not_cut(olst, e))
		{
			if (hit_not_cut(hit, olst, ray))
				hit_anything = 1;
		}
		olst = olst->next;
	}
	return (hit_anything);
}

void	blinding_lights(t_env *e)
{
	int			i;
	t_hit_rec	hit_rec;
	t_hit_rec	hit_light;
	t_ray		ray;

	e->z = 500;
	e->y = 500;
	hit_rec.nr = 1;
	hit_rec.nt = 5;
	ray = create_ray(e->y, e->z, e->eye_rot, e->eye_lookfrom);
	nearest_node(e, ray, &hit_rec);
	nearest_light(e, ray, &hit_light);
	i = -1;
	if (nearest_light(e, ray, &hit_light))
		if (hit_light.t < hit_rec.t)
			while (++i < WINY * WINZ)
				e->imgstr[i] = mix_colors(0xFFFFFF, e->imgstr[i], 0.8);
}
