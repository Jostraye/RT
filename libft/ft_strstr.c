/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:11:45 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 14:19:58 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		l;
	char	*ptr;

	l = 0;
	i = 0;
	ptr = (char *)haystack;
	while (needle[l] != '\0')
		l++;
	if (l == 0)
		return (ptr);
	while (ptr[i] != '\0')
	{
		j = 0;
		while (ptr[i + j] == needle[j])
		{
			j++;
			if (needle[j] == '\0')
				return (&ptr[i]);
		}
		i++;
	}
	return (0);
}
