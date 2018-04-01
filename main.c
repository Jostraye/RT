/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:03:28 by jostraye          #+#    #+#             */
/*   Updated: 2018/04/01 14:06:37 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#define DST_IMG 100

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

double delta_calc(double a, double b, double c)
{
	return((b * b) - (4.0 * a * c));
}

int object_cross(t_env *e, int x, int y, int k)
{
	double delta;
	double Vx;
	double Vy;
	double Vz;
	double a;
	double b;
	double c;
	double dirx = (double)(e->eye.x - e->objects[k].where.x);
	double diry = (double)(e->eye.y - e->objects[k].where.y);
	double dirz = (double)(e->eye.z - e->objects[k].where.z);
	Vx = (double)(e->eye.x);
	Vy = (double)(e->eye.y - SIZE / 2 + x);
	Vz = (double)(e->eye.z - SIZE / 2 + y);
	a = (double)(Vx * Vx + Vy * Vy + Vz * Vz);
	b = (double)(2.0 * ((double)(dirx * Vx) + (double)(diry * Vy) + (double)(diry * Vz)));
	c = (double)(dirx * dirx + diry * diry + dirz * dirz - (double)(e->objects[k].what.length *  e->objects[k].what.length));
	delta = delta_calc(a, b, c);
	return (delta < 0 ? 0 : 1);

}

void	*create_image(void *arg)
{
	t_env *e;
	int i;
	int j;
	int k;

	e = (t_env *)arg;


	k = 0;

	while (k < e->numberobjects)
	{
		i = 0;
		j = (e->thread_int) * SIZE / TH_NB;
		printf("%d\n", k);
		while (j < (((e->thread_int + 1) * SIZE) / TH_NB))
		{
			while (i < SIZE)
			{
				if (k == 0)
					e->data[j * SIZE + i] = 0;
				if (object_cross(e, i, j, k))
					e->data[j * SIZE + i] = e->objects[k].what.color;
				// printf("k %d n %d\n", k, object_cross(e, i, j, k));
				if (e->data[j * SIZE + i] == 0)
					e->data[j * SIZE + i] = 0xFFFFFF;
				i++;
			}
			i = 0;
			j++;
		}
		k++;
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
	obj = (t_object *)malloc(2 * sizeof(t_object));
	obj[0].where.x = -1000;
	obj[0].where.y = -400;
	obj[0].where.z = 0;
	obj[0].what.shape = "sphere";
	obj[0].what.length = 500;
	obj[0].what.color = 0x4d0098;
	obj[1].where.x = -1000;
	obj[1].where.y = -300;
	obj[1].where.z = 00;
	obj[1].what.shape = "sphere";
	obj[1].what.length = 500;
	obj[1].what.color = 0x984d00;
	e->numberobjects = 2;
	e->objects = obj;
	e->eye.x = SIZE;
	e->eye.y = -400;
	e->eye.z = 00;
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
