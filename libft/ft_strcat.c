/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 18:53:42 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/29 18:53:53 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *restrict str1, const char *restrict str2)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str1[i] != '\0')
		i++;
	while (str2[j] != '\0')
		str1[i++] = str2[j++];
	str1[i] = '\0';
	return (str1);
}
