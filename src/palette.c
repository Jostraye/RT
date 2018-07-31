/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:31:45 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/24 13:47:01 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		palette_compare(int *palette, int color)
{
		int	i;

		i = 0;
		while (i < PALETTE_SIZE)
		{
			if (palette[i] < 0)
				return (i);
			if (clr_abs_dif(color, palette[i]) < CART_S)
				return (0);
			if (clr_abs_dif(color, palette[i]) >= CART_S)
				i++;
		}
		return (i);
}

int		palette_add(int *palette, int color)
{
	int i;

	i = -1;
	while (palette[++i] != -1 && i < PALETTE_SIZE)
	if (i <= PALETTE_SIZE)
		return (color);
	return (-1);
}

char	init_palette(int *palette)
{
	int i;

	i = 0;
	while(i < PALETTE_SIZE)
	{
		palette[i] = -1;
		i++;
	}
	palette[0] = 0xffffff;
	if (i == PALETTE_SIZE)
		return (1);
	return (0);
}

char	create_palette(t_env *e, int *palette)
{
	int i;
	int y;
	int z;

	i = 0;
	z = -1;
	while (++z < WINZ)
	{
		y = -1;
		while (++y < WINY)
		if (palette_compare(palette, e->imgstr[z * WINY + y]) && i < PALETTE_SIZE)
			{
				palette[i] = palette_add(palette, e->imgstr[z * WINY + y]);
				i++;
			}
	}
	if (i == PALETTE_SIZE && palette[0] != palette[1] && palette[1] != palette[2])
		return (1);
	return (0);
}
