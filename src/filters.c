/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:06:54 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/19 13:27:00 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

// All filters fo the RT projects will be set here
//
void	stereoscopic(t_env *e)
{
	int *colorcopy;
	int			px_color;
	t_ray		ray;
	t_hit_rec	hit_rec;
	int i;

	i= 0;
	colorcopy = (int *)malloc(sizeof(int) * WINY * WINZ);
	global_filter(e, 2);
	e->z = (e->thread_int) * WINZ / TH_NB - 1;
	e->eye_lookfrom.y -= 60;
	while (++(e->z) < ((e->thread_int + 1) * WINZ) / TH_NB)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			colorcopy[e->z * WINY + e->y] = e->imgstr[e->z * WINY + e->y];
			hit_rec.nr = 1;
			hit_rec.nt = 56;
			ray = create_ray(e->y, e->z, e->eye_rot, e->eye_lookfrom);
			if (nearest_node(e, ray, &hit_rec))
			{
				px_color = compute_point(e, &hit_rec, ray);
				draw_point(e, e->y, e->z, px_color);
			}
		}
	}
	global_filter(e, 3);
	while (++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
		e->imgstr[i] = add_color(e->imgstr[i], colorcopy[i]);
}

int	sepia_filter(t_env *e, int i)
{
	t_vc rgb;
	t_vc sepiargb;
	int color;

	color = 0;
	rgb = hextorgb(e->imgstr[i]);
	sepiargb.x = ((double)(rgb.x * 393) + (rgb.y * 769) + (rgb.z * 189)) / 1000;
	sepiargb.y = ((double)(rgb.x * 349) + (rgb.y * 686) + (rgb.z * 168)) /1000;
	sepiargb.z = ((double)(rgb.x * 272) + (rgb.y * 534) + (rgb.z * 131)) /1000;
	color = color_limits(sepiargb.x) * 256 * 256 +
	color_limits(sepiargb.y) * 256 + color_limits(sepiargb.z);
	return (color);
}

void global_filter(t_env *e, int filter)
{
	int i;

	i = ((e->thread_int) * WINZ / TH_NB) * WINY - 1;
	if (filter == -1 || !filter)
		exit (0);
	if (filter == 0)
	while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
		e->imgstr[i] = e->imgstr[i] % 0X100;
	if (filter == 1)
	while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
		e->imgstr[i] = ((e->imgstr[i] / 0X100) % 0X100) * 0X100;
	if (filter == 2)
	while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
		e->imgstr[i] = ((e->imgstr[i] / (0X100 * 0X100)) % 0X100) * (0X100 * 0X100);
	if (filter == 3)
	while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
		e->imgstr[i] = e->imgstr[i] % 0X100 + ((e->imgstr[i] / 0X100) % 0X100) * 0X100;
	if (filter == 4)
		while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
			e->imgstr[i] = sepia_filter(e, i);
}
