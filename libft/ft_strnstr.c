/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:11:33 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 14:20:43 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	int			l;
	char		*ptr;

	l = 0;
	i = 0;
	ptr = (char *)haystack;
	while (needle[l] != '\0')
		l++;
	if (l == 0)
		return (ptr);
	while (ptr[i] != '\0' && i < len)
	{
		j = 0;
		while (ptr[i + j] == needle[j])
		{
			j++;
			if (needle[j] == '\0' && (i + j) <= len)
				return (&ptr[i]);
		}
		i++;
	}
	return (0);
}
