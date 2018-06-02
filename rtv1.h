/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 20:28:14 by jostraye          #+#    #+#             */
/*   Updated: 2018/06/02 12:25:20 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include "mlx.h"
# define SIZE 1200
# define BUFF_SIZE 100
# define WIN_H 1000
# define WIN_W 1000
# define CLR 0x333d3f
# define TH_NB 16

typedef struct		s_vect
{
	double					x;
	double					y;
	double					z;
}									t_vect;

typedef struct		s_cross
{
	t_vect					norm;
	double					dist;
}									t_cross;

typedef struct		s_what
{
	char						*shape;
	double					length;
	int							color;
}									t_what;

typedef struct		s_matrix
{
	double					xa;
	double					ya;
	double					za;
	double					xb;
	double					yb;
	double					zb;
	double					xc;
	double					yc;
	double					zc;

}									t_matrix;

typedef struct		s_object
{
	t_vect					where;
	t_what					what;
	t_vect					direct;
}									t_object;

typedef struct		s_scene
{
	t_object	*objects;
	t_object	spot;
	t_object	eye;
}									t_scene;


typedef struct		s_env
{
	t_object	*objects;
	t_object	spot;
	t_object	eye;
	int				numberobjects;
	void			*mlx;
	void			*win;
	void			*img;
	pthread_t		pth[TH_NB];
	double			thread_int;
	int				key_code;
	int				*data;
	int				bpp;
	int				ls;
	int				endian;
}					t_env;

typedef struct		s_thread
{
	t_env			*env;
	int				id;
}					t_thread;

int				get_next_line(const int fd, char **line);
t_object *get_scene(char **argv);
int				get_nb_line(char *av);
t_vect vect_mult(double a, t_vect V);
t_matrix rotate_matrix(t_vect a);
t_vect	vect_bind(t_vect a, t_vect b);
double vect_norm(t_vect a);
double vect_scal(t_vect a, t_vect b);
double vect_angle(t_vect a, t_vect b);
double delta_calc(t_vect A);
t_vect matrix_mult(t_vect a, t_matrix b);
t_vect	vect_add(t_vect a, t_vect b);
t_matrix inverse_matrix(t_vect a);
int ft_sign(double a);



// int		expose_hook(t_env *e);
// int		mouse_click_hook(int k, int x, int y, t_env *e);
// int		mouse_pos(int x, int y, t_env *e);
// int		keyboard_hooks(int key_code, t_env *e);

#endif
