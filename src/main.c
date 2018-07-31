/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/16 15:28:33 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int ac, char **av)
{
	t_env *e;

	if (ac != 2)
		ft_usage();
	if (!(e = init_env()))
		exit_message("Problem while creating environment structure\n");
	e->obj_link = NULL;
	e->light_link = NULL;
	e->cut_link = NULL;
	if (!parser(av, e))
		exit_message("Problem while opening file\n");
	pthread_mutex_init(&(e->mutex), NULL);
	if (e->nb_eye != 1)
		error_messages(6);
	if (!init_mlx(e))
		exit_message("Problem while creating MLX environment\n");

	if (!(create_image(e)))
		exit_message("Problem while creating image\n");
	mlx_hook(e->win, 2, 3, deal_key, e);
	mlx_mouse_hook(e->win, deal_mouse, e);
	mlx_loop(e->mlx);
	clear_list(e->obj_link);
	clear_list(e->light_link);
	clear_list(e->cut_link);
	free(e);
	return (0);
}
