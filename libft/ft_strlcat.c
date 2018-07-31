/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:10:31 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/04 14:10:23 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dst_len;
	size_t		src_len;
	char		*dstcp;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (src_len + size);
	dstcp = dst;
	dstcp += dst_len;
	while (*src && size > 1 + dst_len)
	{
		*dstcp++ = *src++;
		size--;
	}
	*dstcp = '\0';
	return (dst_len + src_len);
}
