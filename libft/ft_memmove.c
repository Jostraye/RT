/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 12:04:05 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/29 16:44:44 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *u;
	char *v;

	v = (char *)src;
	u = (char *)dst;
	if (u > v)
	{
		while (len--)
			u[len] = v[len];
	}
	else
		ft_memcpy(u, v, len);
	return (u);
}
