/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 08:30:53 by jostraye          #+#    #+#             */
/*   Updated: 2017/10/02 19:05:12 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int sum;
	int	bol;

	bol = 1;
	sum = 0;
	i = 0;
	while ((str[i] == '\t') || (str[i] == '\n') || (str[i] == '\v') ||
	(str[i] == '\f') || (str[i] == ' ') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		bol = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		sum *= 10;
		sum += (int)str[i] - '0';
		i++;
	}
	return (sum * bol);
}
