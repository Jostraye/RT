/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:07:44 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/06 12:18:23 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
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
		if (srccpy[i] == (unsigned char)c)
			return (&destcp[i + 1]);
		i++;
	}
	return (NULL);
}
