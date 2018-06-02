/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpackcount.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:37:03 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/29 19:26:34 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_charpackcount(const char *s, char c)
{
	int i;
	int j;

	j = -1;
	i = 0;
	while (s[j++])
		if (s[j] == c && (s[j - 1] != c || s[j + 1] != c))
			i++;
	return (i);
}
