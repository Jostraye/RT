/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:11:37 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 14:20:55 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	if (ft_strchr(s, c) == NULL)
		return (NULL);
	while (*ptr)
		ptr++;
	while (*ptr != (char)c)
		ptr--;
	return (ptr);
	return (0);
}
