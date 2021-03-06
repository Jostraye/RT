/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 17:39:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/05 18:22:20 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_factorial(int nb)
{
	if (nb == 0)
		return (1);
	if (nb > 0 && nb < 13)
		return (nb * (ft_factorial(nb - 1)));
	else
		return (0);
}
