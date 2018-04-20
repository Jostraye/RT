/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 20:28:14 by jostraye          #+#    #+#             */
/*   Updated: 2018/04/20 15:01:24 by jostraye         ###   ########.fr       */
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
# define SIZE 1000
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
	double					height;
	double					width;
	int							color;
	double					reflect;
	double					shine;
	double					fluo;
	double					trans;
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
}									t_object;

typedef struct		s_light
{
	t_vect					where;
	double					intensity;
}									t_light;

typedef struct		s_env
{
	t_object	*objects;
	t_light	spot;
	t_light	eye;
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

// int		expose_hook(t_env *e);
// int		mouse_click_hook(int k, int x, int y, t_env *e);
// int		mouse_pos(int x, int y, t_env *e);
// int		keyboard_hooks(int key_code, t_env *e);

#endif
