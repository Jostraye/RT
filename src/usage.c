/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:57:03 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/21 13:21:54 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_usage(void)
{
	ft_putstr_fd("Usage:\n", 2);
	ft_putstr_fd("./rtv1 scene_file\n", 2);
	exit(1);
}

void		ft_malloc_error(t_env *e)
{
	ft_putstr_fd("Problem while malloc\n", 2);
	free(e);
	exit(1);
}

void		exit_message(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}
