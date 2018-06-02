/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 14:31:42 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/29 17:45:03 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*d;

	if (s == NULL)
		return (NULL);
	else
		d = (char *)malloc(ft_strlen((char *)s) + 1);
	if (d == NULL)
		return (NULL);
	i = 0;
	if (s[i])
		while (s[i] != '\0')
		{
			d[i] = f(i, (char)s[i]);
			i++;
		}
	d[i] = '\0';
	return (d);
}
