/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:58:40 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/03 19:21:06 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*ret;
	t_list		*cpy;

	if (!lst)
		return (NULL);
	cpy = NULL;
	ret = f(lst);
	cpy = ret;
	while (lst->next)
	{
		ret->next = f(lst->next);
		lst = lst->next;
		ret = ret->next;
	}
	return (cpy);
}
