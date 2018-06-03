/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:03:28 by jostraye          #+#    #+#             */
/*   Updated: 2018/06/03 17:13:07 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#define DST_IMG 1000
#define ANGL_CVRT 0.0174532925

t_vect compute_distance(t_vect V, t_vect dir, t_env *e, int k)
{
	t_vect A;

	if (strcmp(e->objects[k].what.shape, "cone") == 0)
	{
	A.x = (double)(V.x * V.x + V.y * V.y - V.z * V.z / e->objects[k].what.length);
	A.y = (double)(2.0 * ((double)(dir.x * V.x) + (double)(dir.y * V.y)
	- (double)(dir.z * V.z / e->objects[k].what.length)));
	A.z = (double)(dir.x * dir.x + dir.y * dir.y - dir.z * dir.z
		/ e->objects[k].what.length);
	}
	if (strcmp(e->objects[k].what.shape, "cylindre") == 0)
	{
	A.x = (double)(V.x * V.x + V.y * V.y );
	A.y = (double)(2.0 * ((double)(dir.x * V.x) + (double)(dir.y * V.y)));
	A.z = (double)(dir.x * dir.x + dir.y * dir.y - e->objects[k].what.length
		* e->objects[k].what.length);
	}
	if (strcmp(e->objects[k].what.shape, "sphere") == 0)
	{
		A.x = (double)(V.x * V.x + V.y * V.y + V.z * V.z);
		A.y = (double)(2.0 * ((double)(dir.x * V.x) + (double)(dir.y * V.y)
		+ (double)(dir.z * V.z)));
		A.z = (double)(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z -
			 (double)(e->objects[k].what.length *  e->objects[k].what.length));
	}
	return (A);
}

t_vect compute_norm(t_vect V, t_env *e, int k, double distance)
{
	t_vect N;
	N = vect_mult(distance, V);
	if (strcmp(e->objects[k].what.shape, "cone") == 0)
		N.z = - vect_mult(distance, V).z / e->objects[k].what.length;
	if (strcmp(e->objects[k].what.shape, "cylindre") == 0)
		N.z = e->objects[k].where.z;
	return (N);
}

t_cross circular_crossing(t_vect V, t_vect dir, t_env *e, int k)
{
	double delta;
	double discr[2];
	t_vect A;
	t_cross cross_info;

	discr[0] = -2147483647;
	discr[1] = -2147483647;
	A = compute_distance(V, dir, e, k);
	delta = delta_calc(A);
	if (delta >= 0)
	{
		discr[0] = (- A.y + sqrt(delta)) / (2 * A.x);
		discr[1] = (- A.y - sqrt(delta)) / (2 * A.x);
	}
	cross_info.dist = discr[0] < discr[1] ? discr[0] : discr[1];
	cross_info.norm = compute_norm(V, e, k, cross_info.dist);
	return (cross_info);
}

t_cross plane_crossing(t_vect V, t_vect dir, t_env *e, int k)
{
	t_cross cross_info;
	t_matrix rotate;

	rotate = rotate_matrix(e->objects[k].direct);
	cross_info.norm.x = 0;
	cross_info.norm.y = 0;
	cross_info.norm.z = 100;
	if (V.z != 0)
		cross_info.dist = ( - dir.z) / V.z;
	else
		cross_info.dist = -247483647;
	// cross_info.norm = vect_mult(ft_sign(e->objects[k].where.z),cross_info.norm);
	// cross_info.norm = vect_bind(vect_mult(cross_info.dist, V), cross_info.norm);
	return (cross_info);
}

t_vect init_v_vect( int i, int j)
{
	t_vect V;

	V.x = (double)(DST_IMG);
	V.y = (double)(SIZE / 2 - i);
	V.z = (double)(SIZE / 2 - j);
	return (V);
}

t_cross object_cross(t_env *e, t_vect V, t_vect dir, int k)
{
	t_cross crossing;
	t_matrix rotate;
	rotate = rotate_matrix(e->objects[k].direct);

	// dir = e->eye.where;
	rotate = inverse_matrix(e->objects[k].direct);
	if (strcmp(e->objects[k].what.shape, "plane"))
		crossing = circular_crossing(V, dir, e, k);
	else
		crossing = plane_crossing(V, dir, e, k);
	if (strcmp(e->objects[k].what.shape, "plane") != 0)
	// {
		crossing.norm = vect_add(matrix_mult(crossing.norm, rotate), e->eye.where);
	crossing.norm = vect_bind(e->objects[k].where, crossing.norm);
	// }
	return (crossing);
}

int multiply_color(int hex, double mult)
{
	int r;
	int g;
	int b;

	if (mult < 0)
		mult = 0;
	b = (hex % 0X100);
	g = (hex / 0X100) % 0X100;
	r = (hex / (0X100 * 0X100)) % 0X100;
		hex = (int)(mult * b) + (int)(mult * g) * 0X100 + (int)(mult * r) * 0X100 * 0X100 ;
	return (hex);
}

double shadowing(double a)
{
	if (a > 0 && a < 1)
		return ((double)0.35);
	else
	return((double)1);
}

void	*create_image(void *arg)
{
	t_env *e;
	int i;
	int j;
	int k;
	t_vect V;
	t_vect dir;
	t_vect L;
	t_vect Ldir;
	t_matrix rotate;
	t_vect *normal_vectors;
	double *shadow;
	double *pixel_distance;
	t_vect *point_on_shape;
	int *is_object;

	e = (t_env *)arg;
	normal_vectors = (t_vect *)malloc((sizeof(t_vect) * SIZE * SIZE));
	point_on_shape = (t_vect *)malloc((sizeof(t_vect) * SIZE * SIZE));
	pixel_distance = (double *)malloc((sizeof(double) * SIZE * SIZE));
	shadow = (double *)malloc((sizeof(double) * SIZE * SIZE));
	is_object = (int *)malloc((sizeof(int) * SIZE * SIZE));
	k = 0;
	while (k < e->numberobjects - 2)
	{
		i = 0;
		j = (e->thread_int) * SIZE / TH_NB;
		while (j < (((e->thread_int + 1) * SIZE) / TH_NB))
		{
			while (i < SIZE)
			{
				rotate = rotate_matrix(e->objects[k].direct);
				V = matrix_mult(init_v_vect(i, j), rotate);
				dir = matrix_mult(vect_bind(e->objects[k].where,e->eye.where), rotate);
				if (k == 0)
				{
					pixel_distance[j * SIZE + i] = object_cross(e, V, dir, k).dist;
					is_object[j * SIZE + i] = k;
					normal_vectors[j * SIZE + i] = object_cross(e, V, dir, k).norm;
				}
				if ((object_cross(e, V, dir, k).dist < pixel_distance[j * SIZE + i] && object_cross(e, V, dir, k).dist > 0) || pixel_distance[j * SIZE + i] < 0)
					{
						pixel_distance[j * SIZE + i] = object_cross(e, V, dir, k).dist;
						is_object[j * SIZE + i] = k;
						normal_vectors[j * SIZE + i] = object_cross(e, V, dir, k).norm;
					}
        // on retourne sur le vecteur V non trqnsforme pour calcler la distance du point
				V = init_v_vect(i, j);
				point_on_shape[j * SIZE + i] = vect_mult(pixel_distance[j * SIZE + i], V);
				// a parti d'ici on peut refaire la procedure pour calculer les ombres


				i++;
			}
			i = 0;
			j++;
		}
		k++;
	}
	k = 0;
	while (k < e->numberobjects - 2)
	{
		i = 0;
		j = (e->thread_int) * SIZE / TH_NB;
		while (j < (((e->thread_int + 1) * SIZE) / TH_NB))
		{
			while (i < SIZE)
			{
				rotate = rotate_matrix(e->objects[k].direct);
				L = matrix_mult(vect_bind(e->spot.where, vect_add(point_on_shape[j * SIZE + i], e->eye.where)), rotate);
				Ldir = matrix_mult(vect_bind(vect_add(point_on_shape[j * SIZE + i], e->eye.where), e->objects[k].where), rotate);
				if (k == 0)
					shadow[j * SIZE + i] = object_cross(e, L, Ldir, k).dist;
				else if ((shadow[j * SIZE + i] >= 1  || shadow[j * SIZE + i] <= 0))
					shadow[j * SIZE + i] = object_cross(e, L, Ldir, k).dist;
					// printf("%f\n", shadow[j * SIZE + i]);
				i++;
			}
			i = 0;
			j++;
		}
		k++;
	}
	k = 0;
	while (k < e->numberobjects - 2)
	{
		i = 0;
		j = (e->thread_int) * SIZE / TH_NB;
		while (j < (((e->thread_int + 1) * SIZE) / TH_NB))
		{
			while (i < SIZE)
			{
			L = vect_bind(e->spot.where, vect_add(point_on_shape[j * SIZE + i], e->eye.where));
			if (pixel_distance[j * SIZE + i] < 0)
				is_object[j * SIZE + i] = -1;
			if (k == 0)
				e->data[j * SIZE + i] = -2147483648;
			if (pixel_distance[j * SIZE + i] >= 0 && pixel_distance[j * SIZE + i] < 2000 )
				e->data[j * SIZE + i] = multiply_color(e->objects[is_object[j * SIZE + i]].what.color,
					shadowing(shadow[j * SIZE + i]) * vect_angle(vect_mult((double)-1, L), normal_vectors[j * SIZE + i]));
			// else if (shadow[j * SIZE + i] < 1 && shadow[j * SIZE + i] > 0)
			// 	e->data[j * SIZE + i] = 0;
			else if (e->data[j * SIZE + i] == -2147483648)
				e->data[j * SIZE + i] = 0x51220;
			i++;
		}
		i = 0;
		j++;
		}
		k++;
	}
	free(normal_vectors);
	free(pixel_distance);
	free(is_object);
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

t_env	*create_environment(t_env *e, char **av)
{
	int i;
	int j;

	j = 0;
	i = 0;
	e->numberobjects = get_nb_line(av[1]);
	t_object *obj;
	e->objects = malloc(sizeof(t_object) * (e->numberobjects - 1));
	if ((obj = get_scene(av)))
	{
		while (i < e->numberobjects)
		{
			if (ft_strcmp(obj[i].what.shape, "eye") && ft_strcmp(obj[i].what.shape, "spot"))
			{
				e->objects[j] = obj[i];
				j++;
			}
			else if (ft_strcmp(obj[i].what.shape, "eye"))
				e->spot = obj[i];
			else if (ft_strcmp(obj[i].what.shape, "spot"))
				e->eye = obj[i];
			i++;
		}
	}
	else
		return (NULL);
	return (e);
}

int		main(int ac, char **av)
{
	t_env *e;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (0);
	if (av == NULL || ac > 2)
		printf("Please pass a correct number of files\n");
	if ((create_environment(e, av)))
		run_win(e);
	else
		printf ("Please pass a valid configuration file as argument\n");
	return (0);
}
