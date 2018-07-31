/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/17 18:16:47 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ratio_limits(double i)
{
	if (i < 0.00001)
		return (0);
	if (i > 1.0)
		return (1.0);
	else
		return (i);
}

int			color_limits(int col)
{
	if (col < 0)
		return (0);
	if (col > 255)
		return (255);
	else
		return (col);
}

int			multiply_color(int hex, double mult)
{
	int r;
	int g;
	int b;

	if (mult < 0)
		mult = 0;
	b = color_limits(hex % 0x100);
	g = color_limits((hex / 0x100) % 0x100);
	r = color_limits((hex / (0x100 * 0x100)) % 0x100);
	hex = (int)(mult * b) + (int)(mult * g) * 0x100 +
	(int)(mult * r) * 0x100 * 0x100;
	return (hex);
}

int			add_color(int hex1, int hex2)
{
	int r;
	int g;
	int b;

	r = color_limits((hex1 / (0x100 * 0x100)) % 0x100
		+ (hex2 / (0x100 * 0x100)) % 0x100);
	g = color_limits((hex1 / 0x100) % 0x100 + (hex2 / 0x100) % 0x100);
	b = color_limits(hex1 % 0x100 + hex2 % 0x100);
	return (((int)(r & 0xff) << 16) + ((int)(g & 0xff) << 8) + (int)(b & 0xff));
}

int			mix_colors(int col1, int col2, double coef)
{
	return (add_color(multiply_color(col1, coef), multiply_color(col2, (1 - coef))));
}
