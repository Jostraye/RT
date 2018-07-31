/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:41:16 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/23 10:44:37 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long conversion;
	char *final;
	long i;

	conversion = ft_atoi_base(nbr, ft_strlen(base_from));
	if (conversion < 0)
	{
		final = ft_itoa_base(-conversion, base_to);
		i = ft_strlen(final);
		while (i >= 0)
		{
			final[i + 1] = final[i];
			i--;
		}
		final[0] = '-';
		return (final);
	}
	else if (conversion == 0)
		return ("0");
	else
		return (ft_itoa_base(conversion, base_to));
}
