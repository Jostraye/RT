/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:47:27 by jostraye          #+#    #+#             */
/*   Updated: 2017/09/29 16:17:35 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *d;

	d = (void *)malloc(size);
	if (d == NULL)
		return (NULL);
	else
	{
		ft_memset(d, 0, size);
		return (d);
	}
}
