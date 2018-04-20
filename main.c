/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:03:28 by jostraye          #+#    #+#             */
/*   Updated: 2018/04/16 19:10:36 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#define DST_IMG 1000

t_vect matrix_transform(t_vect a, t_matrix b)
{
	t_vect c;
	c.x = a.x * b.xa + a.y * b.xb + a.z * b.xc;
	c.y = a.x * b.ya + a.y * b.yb + a.z * b.yc;
	c.z = a.x * b.za + a.y * b.zb + a.z * b.zc;
	return (c);
}

t_vect	vect_bind(t_vect a, t_vect b)
{
	t_vect c;
	c.x = b.x - a.x;
	c.y = b.y - a.y;
	c.z = b.z - a.z;
	return (c);
}

double vect_norm(t_vect a)
{
	return (sqrt((double)(a.x * a.x) + (double)(a.y * a.y) + (double)(a.z * a.z)));
}

double vect_scal(t_vect a, t_vect b)
{
	return ((double)(a.x * b.x) + (double)(a.y * b.y) + (double)(a.z * b.z));
}

double vect_angle(t_vect a, t_vect b)
{
	return ((double)vect_scal(a, b) / ((double)(vect_norm(a) * vect_norm(b))));
}

double delta_calc(t_vect A)
{
	return((double)(A.y * A.y) - (double)(4.0 * A.x * A.z));
}

t_cross cone(t_vect V, t_vect dir)
{
	double delta;
	double discr1;
	double discr2;
	t_vect A;
	t_matrix shear;
	shear.xa = 1;
	shear.xb = 0;
	shear.xc = 0;
	shear.ya = 0;
	shear.yb = 1;
	shear.yc = 0.5;
	shear.za = 0;
	shear.zb = 0;
	shear.zc = 1;
	discr1 = 2147483647;
	discr2 = 2147483647;
	t_cross cross_info;

	V = matrix_transform(V, shear);
	dir = matrix_transform(dir, shear);

	A.x = (double)(V.x * V.x + V.y * V.y - V.z * V.z);
	A.y = (double)(2.0 * ((double)(dir.x * V.x) + (double)(dir.y * V.y) - (double)(dir.z * V.z)));
	A.z = (double)(dir.x * dir.x + dir.y * dir.y - dir.z * dir.z);
	delta = delta_calc(A);
	if (delta >= 0)
	{
		discr1 = (- A.y + sqrt(delta)) / (2 * A.x);
		discr2 = (- A.y - sqrt(delta)) / (2 * A.x);
	}
	if (discr2 > 0)
		discr2 = 2147483647;
	if (discr1 > 0)
		discr1 = 2147483647;

	cross_info.dist = discr1 > discr2 ? discr1 : discr2;
	cross_info.x =
	cross_info.y =
	cross_info.z =
	return (cross_info);
}

t_cross cylindre(t_vect V,t_vect dir)
{
	double delta;
	double discr1;
	double discr2;
	t_vect A;
	t_matrix shear;
	shear.xa = 1;
	shear.xb = 0;
	shear.xc = 0;
	shear.ya = 0;
	shear.yb = 1;
	shear.yc = 0.5;
	shear.za = 0;
	shear.zb = 0;
	shear.zc = 0;
	discr1 = 2147483647;
	discr2 = 2147483647;
	t_cross cross_info;

	V = matrix_transform(V, shear);
	dir = matrix_transform(dir, shear);

	A.x = (double)(V.x * V.x + V.y * V.y - V.z * V.z);
	A.y = (double)(2.0 * ((double)(dir.x * V.x) + (double)(dir.y * V.y) - (double)(dir.z * V.z)));
	A.z = (double)(dir.x * dir.x + dir.y * dir.y - dir.z * dir.z - 10000);
	delta = delta_calc(A);
	if (delta >= 0)
	{
		discr1 = (- A.y + sqrt(delta)) / (2 * A.x);
		discr2 = (- A.y - sqrt(delta)) / (2 * A.x);
	}
	if (discr2 > 0)
		discr2 = 2147483647;
	if (discr1 > 0)
		discr1 = 2147483647;
	cross_info.dist = discr1 > discr2 ? discr1 : discr2;
	cross_info.x =
	cross_info.y =
	cross_info.z =
	return (cross_info);

}

t_cross plane(t_vect V, t_vect dir)
{
	t_vect normal;
	t_cross cross_info;

	normal.x = 10;
	normal.y = 0;
	normal.z = 0;
	cross_info.dist = vect_scal(dir, normal) / vect_scal(V, normal);
	cross_info.x = normal.x;
	cross_info.y = normal.y;
	cross_info.z = normal.z;
	return (cross_info);

}

t_cross sphere(t_vect V, t_vect dir, t_env *e, int k)
{
	double delta;
	double discr1;
	double discr2;
	t_cross cross_info;
	t_vect A;

	discr1 = 2147483647;
	discr2 = 2147483647;
	A.x = (double)(V.x * V.x + V.y * V.y + V.z * V.z);
	A.y = (double)(2.0 * ((double)(dir.x * V.x) + (double)(dir.y * V.y) + (double)(dir.z * V.z)));
	A.z = (double)(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z - (double)(e->objects[k].what.length *  e->objects[k].what.length));
	delta = delta_calc(A);
	if (delta >= 0)
	{
		discr1 = (- A.y + sqrt(delta)) / (2 * A.x);
		discr2 = (- A.y - sqrt(delta)) / (2 * A.x);
	}
	if (discr2 > 0)
		discr2 = 2147483647;
	if (discr1 > 0)
		discr1 = 2147483647;
	cross_info.dist = discr1 > discr2 ? discr1 : discr2;
	cross_info.x = e->objects[k].where.x;
	cross_info.y = e->objects[k].where.y;
	cross_info.z = e->objects[k].where.z;
	return (cross_info);
}

t_cross object_cross(t_env *e, int i, int j, int k)
{
	t_cross cross_info;
	t_vect V;
	t_vect dir;
	dir.x = (double)(e->objects[k].where.x);
	dir.y = (double)(e->objects[k].where.y);
	dir.z = (double)(e->objects[k].where.z);
	V.x = (double)(DST_IMG);
	V.y = (double)(SIZE / 2 - i);
	V.z = (double)(SIZE / 2 - j);
	if (strcmp(e->objects[k].what.shape, "sphere") == 0)
		cross_info = sphere(V, dir, e, k);
	if (strcmp(e->objects[k].what.shape, "cone") == 0)
		cross_info = cone(V, dir);
	if (strcmp(e->objects[k].what.shape, "cylindre") == 0)
		cross_info = cylindre(V, dir);
	if (strcmp(e->objects[k].what.shape, "plane") == 0)
		cross_info = plane(V, dir);

	return (cross_info);

}

t_vect vect_mult(double a, t_vect V)
{
	V.x = V.x * a;
	V.y = V.y * a;
	V.z = V.z * a;
	return (V);
}

void	*create_image(void *arg)
{
	t_env *e;
	int i;
	int j;
	int k;
	t_vect V;
	t_vect *points;


	e = (t_env *)arg;
	double *pixel_distance;
	int *pixel_object;

	points = (t_vect *)malloc((sizeof(t_vect) * SIZE * SIZE));
	pixel_distance = (double *)malloc((sizeof(double) * SIZE * SIZE));
	pixel_object = (int *)malloc((sizeof(int) * SIZE * SIZE));

	k = 0;
	while (k < e->numberobjects)
	{
		i = 0;
		j = (e->thread_int) * SIZE / TH_NB;

		while (j < (((e->thread_int + 1) * SIZE) / TH_NB))
		{

			while (i < SIZE)
			{
				points[j * SIZE + i] = vect_bind(e->objects[k].where, vect_mult(-object_cross(e, i, j, k).dist, V));
				V.x = (double)(DST_IMG);
				V.y = (double)(SIZE / 2 - i);
				V.z = (double)(SIZE / 2 - j);
				pixel_object[j * SIZE + i] = k;
				pixel_distance[j * SIZE + i] = -1000 * object_cross(e, i, j, k).dist;
				if (pixel_distance[j * SIZE + i] < 0)
					pixel_object[j * SIZE + i] = -1;

				if (k == 0)
					e->data[j * SIZE + i] = 0;
				if (pixel_distance[j * SIZE + i] >= 0 && pixel_distance[j * SIZE + i] < 15000)
					e->data[j * SIZE + i] = ( 0XFF) * -1 * vect_angle(vect_bind(points[j * SIZE + i], e->spot.where), points[j * SIZE + i]);
				// printf("k %d n %d\n", k, object_cross(e, i, j, k));
				if (e->data[j * SIZE + i] == 0)
					e->data[j * SIZE + i] = 0x000000;
				if (i == 350 && j == 500)
				{
					// printf("x: %f, y:  %f, z: %f\n length: %f\n normal x: %f, normal y:  %f, normal z: %f\n", vect_mult(object_cross(e, i, j, k), V).x,
					// vect_mult(object_cross(e, i, j, k), V).y, vect_mult(object_cross(e, i, j, k), V).z,
					// object_cross(e, i, j, k), vect_bind(e->objects[k].where, vect_mult(-object_cross(e, i, j, k), V)).x, vect_bind(e->objects[k].where, vect_mult(-object_cross(e, i, j, k), V)).y,
					// vect_bind(e->objects[k].where, vect_mult(-object_cross(e, i, j, k), V)).z);
					// printf("angle %f\n", vect_angle(vect_mult(-object_cross(e, i, j, k), V), vect_bind(e->objects[k].where, vect_mult(-object_cross(e, i, j, k), V))));
				}
				i++;
			}
			i = 0;
			j++;
		}
		k++;
	}
	free(points);
	free(pixel_distance);
	free(pixel_object);
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
	obj[0].where.x = 2000;
	obj[0].where.y = 0;
	obj[0].where.z = 0;
	obj[0].what.shape = "plane";
	obj[0].what.length = 300;
	obj[0].what.color = 0x4d0098;
	obj[1].where.x = 2000;
	obj[1].where.y = 0;
	obj[1].where.z = 1000;
	obj[1].what.shape = "sphere";
	obj[1].what.length = 300;
	obj[1].what.color = 0x984d00;
	e->numberobjects = 2;
	e->objects = obj;
	e->eye.x = 0;
	e->eye.y = 0;
	e->eye.z = 0;
	e->spot.where.x = 2000;
	e->spot.where.y = 20000;
	e->spot.where.z = 0;
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
