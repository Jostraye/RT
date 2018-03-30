/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:03:28 by jostraye          #+#    #+#             */
/*   Updated: 2018/01/14 14:00:44 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void	print_error(int err)
// {
// 	if (err == 1)
// 		ft_putstr("Error, you must not pass any argument to the function");
// }

// t_env	*reset_environment(t_env *e)
// {
// 	e->max_it = 1;
// 	return (e);
// }

double delta_calc(int a, int b, int c)
{
	return(b * b - 4 * a * c);
}

int object_cross(t_env *e, int i, int j)
{
	double delta;
	double a;
	double b;
	double c;
	a = (e->eye.x * e->eye.x) + (e->eye.y * e->eye.y + j * j - 2 * e->eye.y * j) +
	(e->eye.z * e->eye.z + i * i - 2 * e->eye.y * i);
	b = 2 * e->eye.x * (e->eye.x - e->objects[0].where.x) +
	2 * (e->eye.y - j) * (e->eye.y - e->objects[0].where.y) +
	2 * (e->eye.z - i) * (e->eye.z - e->objects[0].where.z);
	c = e->eye.x * e->eye.x + e->objects[0].where.x * e->objects[0].where.x - 2 * e->objects[0].where.x * e->eye.x +
	e->eye.y * e->eye.y + e->objects[0].where.y * e->objects[0].where.y - 2 * e->objects[0].where.y * e->eye.y +
	e->eye.z * e->eye.z + e->objects[0].where.z * e->objects[0].where.z - 2 * e->objects[0].where.z * e->eye.z;
	delta = delta_calc(a, b, c);
	return (delta <= 0 ? 0 : 1);

}

void	*create_image(void *arg)
{
	t_env *e;
	int i;
	int j;

	e = (t_env *)arg;

	i = 0;
	j = (e->thread_int) * SIZE / TH_NB;
	while (j < (((e->thread_int + 1) * SIZE) / TH_NB))
	{
		while (i < SIZE)
		{
			// printf("int%d\n", e->objects[0].what.color);
			if (object_cross(e, i, j))
				e->data[j * SIZE + i] = e->objects[0].what.color;
			else
				e->data[j * SIZE + i] = 0xFFFFFF;
			// printf("n %d\n", object_cross(e, i, j));
			i++;
		}
		i = 0;
		j++;
	}
	return (NULL);
}

t_env	*initialize_image(t_env *e)
{
	e->img = mlx_new_image(e->mlx, SIZE, SIZE);
	e->data = (int *)mlx_get_data_addr(e->img, &e->bpp, &e->ls, &e->endian);
	e->ls /= 4;
	return (e);
}


void	send_image_to_window(t_env *e)
{
	int i;

	i = 0;
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	while (e->data[i])
	{
		e->data[i] = 0;
	}
	e->data = NULL;
	// text_to_image(e);
}


int		expose_hook(t_env *e)
{
	int		i;
	t_env	copy[TH_NB];

	i = 0;
	mlx_destroy_image(e->mlx, e->img);
	mlx_clear_window(e->mlx, e->win);
	e = initialize_image(e);
	while (i < TH_NB)
	{
		copy[i] = *e;
		copy[i].thread_int = i;
		pthread_create(&e->pth[i], NULL, create_image, &copy[i]);
		i++;
	}
	while (i--)
		pthread_join(e->pth[i], NULL);
	send_image_to_window(e);
	return (0);
}

t_env	*initialize_win(t_env *e)
{
	// e = reset_environment(e);
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE, SIZE, "MY GRAPH");
	e->img = mlx_new_image(e->mlx, SIZE, SIZE);
	return (e);
}

void	run_win(t_env *e)
{
	e = initialize_win(e);
	// mlx_key_hook(e->win, keyboard_hooks, e);
	mlx_expose_hook(e->win, expose_hook, e);
	// mlx_mouse_hook(e->win, mouse_click_hook, e);
	// mlx_hook(e->win, 6, 0, mouse_pos, e);
	mlx_loop(e->mlx);
}

t_env	*create_environment(t_env *e, char *av)
{
	if (av == NULL)
		return(NULL);
	t_object *obj;
	obj = (t_object *)malloc(sizeof(t_object));
	obj[0].where.x = 50;
	obj[0].where.y = 0;
	obj[0].where.z = 0;
	obj[0].what.shape = "sphere";
	obj[0].what.length = 5;
	obj[0].what.color = 0x98004d;
	e->objects = obj;
	e->eye.x = 0;
	e->eye.y = 0;
	e->eye.z = 0;
	e->spot.where.x = 20;
	e->spot.where.y = 20;
	e->spot.where.z = 20;
	return (e);

}

int		main(int ac, char **av)
{
	t_env *e;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (0);
	if (av == NULL || ac > 1)
		printf("not good number of files\n");
		// print_error(1);
	create_environment(e, *av);
	run_win(e);
	return (0);
}
