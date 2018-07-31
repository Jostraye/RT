/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:06:58 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/05 17:10:31 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		rslt;
	int		sign;

	i = 0;
	rslt = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		rslt = (rslt * 10) + str[i] - 48;
		i++;
	}
	return (sign * rslt);
}
