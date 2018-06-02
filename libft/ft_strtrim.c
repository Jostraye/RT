/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:02:25 by jostraye          #+#    #+#             */
/*   Updated: 2017/10/05 22:10:22 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		start;
	int		length;
	char	*d;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	while (ft_istrim(s[length - 1]))
		length--;
	start = -1;
	while (ft_istrim(s[++start]))
		length--;
	length = (length <= 0) ? 0 : length;
	if (!(d = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	s += start;
	start = -1;
	while (++start < length)
		d[start] = *s++;
	d[start] = '\0';
	return (d);
}
