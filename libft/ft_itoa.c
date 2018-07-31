/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:07:37 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 16:00:19 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len(int n)
{
	int l;

	l = 1;
	while (n >= 10)
	{
		n /= 10;
		l++;
	}
	return (l);
}

char			*ft_itoa(int n)
{
	int		sign;
	int		l;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	l = ft_len(n);
	if (!(res = (char*)malloc(sizeof(char) * (l + sign + 1))))
		return (0);
	res[l + sign] = '\0';
	while (l + sign - 1 >= 0)
	{
		res[l + sign - 1] = n % 10 + '0';
		n /= 10;
		l--;
	}
	if (sign == 1)
		res[0] = '-';
	return (res);
}
