/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:11:51 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 14:24:32 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] != '\0'
			&& (s[start] == ' ' || s[start] == '\t' || s[start] == '\n'))
		start++;
	end = ft_strlen(s);
	while (end > start
			&& (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\n'))
		end--;
	if (start == end)
		return (ft_strnew(1));
	else
		return (ft_strsub(s, start, (end - start)));
}
