/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:07:58 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 17:58:55 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destcp;
	unsigned char		*srccpy;
	size_t				i;

	i = 0;
	destcp = (unsigned char *)dest;
	srccpy = (unsigned char *)src;
	while (i < n)
	{
		destcp[i] = srccpy[i];
		i++;
	}
	return (destcp);
}
