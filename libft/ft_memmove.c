/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:08:07 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 18:02:33 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*destcp;
	unsigned char		*srccpy;

	destcp = (unsigned char *)dest;
	srccpy = (unsigned char *)src;
	if (destcp == srccpy || n <= 0)
		return (destcp);
	if (srccpy > destcp)
		ft_memcpy(destcp, srccpy, n);
	else
	{
		while (n--)
			destcp[n] = srccpy[n];
	}
	return (destcp);
}
