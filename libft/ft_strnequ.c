/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:11:24 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 14:20:27 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int i;

	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (1);
		if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}
