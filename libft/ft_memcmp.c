/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:07:54 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 14:23:09 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*s1cp;
	const unsigned char		*s2cp;
	size_t					i;

	if (n == 0)
		return (0);
	s1cp = (const unsigned char *)s1;
	s2cp = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1cp[i] != s2cp[i])
			return (s1cp[i] - s2cp[i]);
		i++;
	}
	return (0);
}
