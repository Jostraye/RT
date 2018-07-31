/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:04:59 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 10:56:09 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_env		*init_env(void)
{
	t_env *e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	e->nb_eye = 0;
	e->id = 0;
	return (e);
}

int			init_mlx(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		return (0);
	if (!(e->win = mlx_new_window(e->mlx, WINY, WINZ, "RTv1")))
		return (0);
	return (1);
}

t_obj	*disc_for_cylinder(t_obj *cyl, t_vc center)
{
	t_obj	*disc;

	if (!(disc = malloc(sizeof(t_obj))))
		return (NULL);
	disc->size = cyl->size;
	disc->type = 7;
	disc->pos = center;
	disc->rot = cyl->rot;
	disc->col = cyl->col;
	disc->coef = cyl->coef;
	disc->next = NULL;
	return (disc);
}

t_vc		init_vc(double x, double y, double z)
{
	t_vc vc;

	vc.x = (double)x;
	vc.y = (double)y;
	vc.z = (double)z;
	return (vc);
}

void		obj_add(t_obj **beg, t_obj *n)
{
	if (!beg || !n)
		return ;
	else
	{
		n->next = *beg;
		*beg = n;
	}
}
