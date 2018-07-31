/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:10:43 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/19 21:21:05 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_iscolor(char *str)
{
	int color;

	color = ft_htoi(str);
	if (color < 0 || color > 0xFFFFFF)
		return (1);
	else
		return (0);
}

int		ft_isnumber(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '-' || str[i] == '+') && i == 0)
			i++;
		if (str[i] < 48 || str[i] > 57)
			return (1);
	}
	return (0);
}

double	ft_atof(char *c)
{
	double	avant;
	double	apres;
	double	total;
	int		len;

	avant = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	len = ft_strlen(c);
	apres = (double)ft_atoi(c);
	while (len--)
		apres /= 10;
	total = avant + apres;
	if (total < 0.0 || total > 1.0)
		return (-1.0);
	return (total);
}

int		ft_htod(char c)
{
	if (ft_isdigit(c))
		return ((int)(c - 48));
	else if ('A' <= 'c' && 'F' >= c)
		return ((int)(c - 55));
	else if ('a' <= c && 'f' >= c)
		return ((int)(c - 87));
	else
		return (-1);
}

int		ft_htoi(char *str)
{
	int i;
	int color;

	color = 0;
	i = 2;
	while (str[0] != '0' && (str[1] != 'x' || str[1] != 'X'))
		return (-1);
	while (str[i])
	{
		if (ft_htod(str[i]) >= 0)
			color = ft_htod(str[i]) + color * 16;
		i++;
	}
	return (color);
}
