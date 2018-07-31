/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 14:26:30 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/20 16:43:04 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		clr_abs_dif(int col1, int col2)
{
	t_vc rgb1;
	t_vc rgb2;
	int ret;

	rgb1 = hextorgb(col1);
	rgb2 = hextorgb(col2);
	rgb1 = vec_sub(rgb1, rgb2);
	ret = fabs(rgb1.x) + fabs(rgb1.y) + fabs(rgb1.z);
	return (ret);
}

int		av_col_four(int col1, int col2, int col3, int col4)
{
	t_vc rgb;
	t_vc rgb1;
	t_vc rgb2;
	t_vc rgb3;
	t_vc rgb4;
	int ret;

	rgb1 = hextorgb(col1);
	rgb2 = hextorgb(col2);
	rgb3 = hextorgb(col3);
	rgb4 = hextorgb(col4);
	rgb.x = color_limits((rgb1.x + rgb2.x + rgb3.x + rgb4.x) / 4);
	rgb.y = color_limits((rgb1.y + rgb2.y + rgb3.y + rgb4.y) / 4);
	rgb.z = color_limits((rgb1.z + rgb2.z + rgb3.z + rgb4.z) / 4);
	ret = rgb.x * 0x100 * 0x100 + rgb.y * 0x100 + rgb.z;
	return (ret);
}

int		av_col_two(int col1, int col2)
{
	t_vc rgb;
	t_vc rgb1;
	t_vc rgb2;
	int ret;

	rgb1 = hextorgb(col1);
	rgb2 = hextorgb(col2);
	rgb.x = color_limits((rgb1.x + rgb2.x) / 2);
	rgb.y = color_limits((rgb1.y + rgb2.y) / 2);
	rgb.z = color_limits((rgb1.z + rgb2.z) / 2);
	ret = rgb.x * 0x100 * 0x100 + rgb.y * 0x100 + rgb.z;
	return (ret);
}

char	aa_condition(int *imgstr, int y, int z, int sensib)
{
	if (clr_abs_dif(imgstr[z * WINY + y + 1],
		imgstr[z * WINY + y + WINY]) > sensib
	|| clr_abs_dif(imgstr[z * WINY + y + 1],
		imgstr[z * WINY + y - WINY]) > sensib
	|| clr_abs_dif(imgstr[z * WINY + y - 1],
		imgstr[z * WINY + y + WINY]) > sensib
	|| clr_abs_dif(imgstr[z * WINY + y - 1],
		imgstr[z * WINY + y - WINY]) > sensib)
		return (1);
	else
		return (0);
}

void	antialias(int *imgstr)
{
	int *colorcopy;
	int	z;
	int	y;

	z = 0;
	if (!(colorcopy = (int *)malloc(sizeof(int) * WINY * WINZ)))
		return ;
	while (++z < WINZ - 1)
	{
		y = 0;
		colorcopy[z * WINY + y] = imgstr[z * WINY + y];
		while (++y < WINY - 1)
		{
			colorcopy[z * WINY + y] = imgstr[z * WINY + y];
			if (aa_condition(imgstr, y, z, AA_S))
				colorcopy[z * WINY + y] = av_col_two(av_col_four(imgstr[z * WINY + y + 1], imgstr[z * WINY + y + WINY],
				imgstr[z * WINY + y - WINY], imgstr[z * WINY + y - 1 ]), imgstr[z * WINY + y]);
		}
	}
	z = - 1;
	while (++z < WINZ)
	{
		y = -1;
		while (++y < WINY)
			imgstr[z * WINY + y] = colorcopy[z * WINY + y];
	}
	free (colorcopy);
}
