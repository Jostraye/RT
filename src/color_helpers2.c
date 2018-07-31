/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:54:54 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/24 13:50:08 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		closest_col(int *palette, int color)
{
	int min_diff;
	int	i;


	i = -1;
	min_diff = 3 * 256;
	while (++i < PALETTE_SIZE)
		if (clr_abs_dif(color, palette[i]) < min_diff)
			min_diff = clr_abs_dif(color, palette[i]);
	i = 0;
	while (++i < PALETTE_SIZE)
		if (clr_abs_dif(color, palette[i]) == min_diff)
			return (i);
	return (0);
}

int		major_color(int color)
{
		t_vc rgb;

		rgb = hextorgb(color);
		if (rgb.x > rgb.y && rgb.x > rgb.z)
			color = 0xFF0000;
		else if (rgb.y > rgb.x && rgb.y > rgb.z)
			color = 0x00FF00;
		else
			color = 0x0000FF;
		return (color);
}
