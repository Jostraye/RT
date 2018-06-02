/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:37:12 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/30 22:28:47 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*u;
	unsigned char	ch;

	i = 0;
	u = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (u[i] == ch)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
