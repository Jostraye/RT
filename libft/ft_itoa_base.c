/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:39:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/23 12:23:08 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long num, char *base)
{
	int		base_s;
	int		i;
	int		cpt;
	char	*str;
	long	numcp;

	base_s = ft_strlen(base);
	i = -1;
	cpt = 0;
	numcp = num;
	while (numcp > 0)
	{
		numcp /= base_s;
		cpt++;
	}
	if ((str = malloc(sizeof(*str) * cpt + 2)) == 0)
		return (NULL);
	str[cpt] = '\0';
	while (++i < cpt)
	{
		str[i] = base[(num % base_s)];
		num /= base_s;
	}
	return (ft_strrev(str));
}
