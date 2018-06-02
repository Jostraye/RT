/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 09:38:22 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/29 16:25:18 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t			i;
	unsigned char	*u;
	unsigned char	*v;

	v = (unsigned char *)src;
	u = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		u[i] = v[i];
		i++;
	}
	return (dst);
}
