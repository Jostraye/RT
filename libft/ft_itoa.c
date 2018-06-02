/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:37:09 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/29 16:16:53 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlength(int n)
{
	size_t i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	char	*d;
	size_t	i;
	int		m;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	m = n;
	i = ft_intlength(n);
	if (n < 0)
	{
		i++;
		m = -n;
	}
	if (!(d = ft_strnew(i)))
		return (NULL);
	d[--i] = m % 10 + '0';
	while (m /= 10)
		d[--i] = m % 10 + '0';
	if (n < 0)
		d[0] = '-';
	return (d);
}
