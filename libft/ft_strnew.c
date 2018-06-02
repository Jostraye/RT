/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 17:32:36 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/29 18:32:43 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*d;

	d = (char *)malloc(size + 1);
	i = 0;
	if (d != NULL)
	{
		while (i != (size + 1))
		{
			d[i] = '\0';
			i++;
		}
		return (d);
	}
	else
		return (NULL);
}
