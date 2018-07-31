/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:36:58 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/23 10:39:33 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ret_nb_b(char c, int str_base)
{
	int		i;
	char	*basel;
	char	*baseu;

	basel = "0123456789abcdef";
	baseu = "0123456789ABCDEF";
	i = 0;
	while (i < str_base)
	{
		if (c == basel[i] || c == baseu[i])
			return (i);
		i++;
	}
	return (-1);
}

int				ft_atoi_base(const char *str, int str_base)
{
	int neg;
	int res;

	res = 0;
	neg = 1;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (ret_nb_b(*str, str_base) == -1)
			return (0);
		res = res * str_base + ret_nb_b(*str, str_base);
		str++;
	}
	return (res * neg);
}
