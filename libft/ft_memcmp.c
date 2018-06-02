/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:37:15 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/29 16:25:45 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*u;
	unsigned char	*v;

	i = 0;
	u = (unsigned char *)s1;
	v = (unsigned char *)s2;
	while (i < n)
	{
		if (u[i] != v[i])
			return (u[i] - v[i]);
		i++;
	}
	return (0);
}
