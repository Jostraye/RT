/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:07:50 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 14:23:59 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*scp;
	unsigned char	cc;
	size_t			i;

	i = 0;
	scp = (unsigned char *)s;
	cc = (unsigned char)c;
	if (n <= 0)
		return (NULL);
	while (i < n)
	{
		if (cc == scp[i])
			return (&scp[i]);
		i++;
	}
	return (NULL);
}
