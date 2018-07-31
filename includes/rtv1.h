/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 11:01:00 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 18:10:33 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# define WINY 1000
# define WINZ 1000
# define FOV 1000
# define TH_NB 50
# define SPHERE_TEXTURE 1
# define CONE_TEXTURE 1
# define CYLINDER_TEXTURE 1
# define PLANE_CHECKERS 0
# define ALPHA_SPEC 100
# define SHADOW_BIAS 0.001
# define AA_S 20
# define CART_S 50
# define PALETTE_SIZE 40

typedef struct		s_vc
{
	double			x;
	double			y;
	double			z;
}					t_vc;

typedef struct		s_ray
{
	t_vc			origin;
	t_vc			direction;
	int				type;
}					t_ray;

typedef struct		s_vclist
{
	t_vc			vector;
	struct s_vclist	*next;
}					t_vclist;

typedef struct		s_obj
{
	int				type;
	t_vc			rot;
	t_vc			pos;
	t_vc			coef;
	int				col;
	double			size;
	double			r;
	double			tr;
	int				id_cut;
	int				id_obj;
	int				*texture_size;
	int				**texture_tab;
	t_vc			lm;
	t_vc			rm;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_hit_rec
{
	double			cost;
	double			t;
	double			t1;
	double			t2;
	double			tr_max;
	int				nr;
	int				nt;
	char			lit;
	t_vc			n;
	t_vc			s;
	t_vc			v;
	t_vc			lm;
	t_vc			hit_inter;
	t_obj			*hit_obj;
}					t_hit_rec;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*image;
	char			*file_name;
	int				*imgstr;
	int				thread_int;
	int				y;
	int				z;
	int				nb_eye;
	int				filter;
	int				id;
	t_vclist		*b_lights;
	t_vc			eye_lookfrom;
	t_vc			eye_rot;
	pthread_t		pth[TH_NB];
	pthread_mutex_t	mutex;
	t_obj			*obj_link;
	t_obj			*light_link;
	t_obj			*cut_link;
}					t_env;

/*
** RAYTRACER
*/

int					create_image(t_env *e);
void				draw_point(t_env *e, int x, int y, unsigned int color);
void				*scene_plot(void *arg);
t_ray				create_ray(int y, int z, t_vc eye_rot, t_vc ray_origin);
double				distance_to_inter(t_hit_rec *hit, t_obj *obj_list, t_ray ray);
char				nearest_node(t_env *e, t_ray ray, t_hit_rec *hit);
void				compute_scene_vectors(t_env *e, t_obj *tmp);
int					is_not_cut(t_obj *obj, t_env *e);
int					mix_colors(int col1, int col2, double coef);

/*
** MATHS
*/

double				car(double a);
t_vc				rot_x(t_vc vc, int t);
t_vc				rot_y(t_vc vc, int t);
t_vc				rot_z(t_vc vc, int t);
t_vc				rot_all_axis(t_vc vc, t_vc obj);
t_vc				rot_all_axis_inv(t_vc vc, t_vc obj);
double				vec_squ_sum(t_vc v1);
t_vc				vec_add(t_vc v1, t_vc v2);
t_vc				vec_sub(t_vc v1, t_vc v2);
t_vc				vec_subp(t_vc *v1, t_vc *v2);
t_vc				vec_croise(t_vc *v1, t_vc *v2);
double				vec_x(t_vc v1, t_vc v2);
double				vec_mod(t_vc v);
t_vc				vec_norm(t_vc v);
t_vc				vec_mult(t_vc v, double x);
double				vec_dot(t_vc v1, t_vc v2);
t_vc				inter_position(t_ray ray, double t);

/*
** SHAPES INTERSECTIONS
*/

double				inter_light(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				inter_sph(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				inter_cone(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				inter_plane(t_ray ray, t_obj *obj);
double				inter_cyl(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				inter_paraboloid(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				quadratic_solver(t_hit_rec *hit, t_vc abc);
char				hit_not_cut(t_hit_rec *hit, t_obj *obj, t_ray ray);
char				hit_cut(t_hit_rec *hit, t_env *e, t_obj *obj, t_ray ray);


/*
** KEYBOARD / MOUSE
*/

void				translation(int key, t_env *e);
void				rotation(int key, t_env *e);
int					deal_key(int key, t_env *e);
int					deal_mouse(int k, int y, int z, t_env *e);

/*
** LIGHTING
*/

t_vc				normal_vectors(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				shadows(t_env *e, t_hit_rec *hit, t_obj *light_obj, t_ray ray);

/*
** COLOR CALCULATION
*/

int					add_color(int hex1, int hex2);
double				ratio_limits(double i);
int					multiply_color(int hex, double mult);
int					color_limits(int col);
int					closest_col(int *palette, int color);
int					major_color(int color);


int					specular_diffuse(t_obj *light, t_hit_rec *hit);
void				global_filter(t_env *e, int filter);



/*
** STRUCTURES INITIALIZATION
*/

t_env				*init_env(void);
int					init_mlx(t_env *e);
t_vc				init_vc(double x, double y, double z);

/*
** OBJECTS
*/

void				obj_add(t_obj **beg, t_obj *n);
void				clear_list(t_obj *head);
t_obj				*disc_for_cylinder(t_obj *cyl, t_vc center);
t_obj				*get_cutter(t_env *e, t_obj *obj);

/*
** ERROR MGT
*/

void				ft_usage(void);
void				ft_malloc_error(t_env *e);
void				exit_message(char *str);

/*
** FREE STRUCTURES
*/

void				free_split(char **split);

/*
** TEXTURES CYLINDER / CONE
*/

char				get_lines_cylinder(t_hit_rec *hit, t_ray ray);
char				get_lines_cone(t_hit_rec *hit, t_ray ray);

/*
** TEXTURES SPHERE /PLANE
*/

char				get_lines_sphere(t_hit_rec *hit, t_ray ray);
char				get_columns_sphere(t_hit_rec *hit, t_ray ray);
char				get_checkerboard_sphere(t_hit_rec *hit, t_ray ray);
int					get_texture_sphere(t_hit_rec *hit, t_ray ray);
char				checkerboard_plane(t_hit_rec *hit, t_ray ray);

/*
** TEXTURES CHOSER
*/

char				textures_coef(t_obj *obj, t_hit_rec *hit, t_ray ray);

/*
** TEXTURE LOADER
*/

int					load_texture_to_obj(t_obj *obj);

/*
** PARSER
*/

int					ft_htod(char c);
int					ft_htoi(char *str);
double				ft_atof(char *c);
int					ft_iscolor(char *str);
int					ft_isnumber(char *str);
int					check_value(char **str);
int					name_type(char *str);
void				error_messages(int error);
t_obj				*attribute_object(char **tab_values, t_env *e);
char				*tabtospace(char *str);
int					attribute_scene(char *str, t_env *e);
int					parser(char **av, t_env *e);
int					create_objects(t_env *e, char **tab_values);

/*
** PALETTE
*/

int					palette_compare(int *palette, int color);
int					palette_add(int *palette, int color);
char				init_palette(int *palette);
char				create_palette(t_env *e, int *palette);

/*
** MISCELLANEOUS
*/

void				create_bmp_file(int *imgstr);
t_vc				hextorgb(int hex);
void				stereoscopic(t_env *e);
void				antialias(int *imgstr);
int					recursive_reflection(t_env *e, int old_color, t_ray ray, t_hit_rec *hit);
int					compute_point(t_env *e, t_hit_rec *hit, t_ray ray);
int					transparency(t_env *e, int old_color, t_ray ray, t_hit_rec *hit);
char				cartooning(t_env *e);
int					clr_abs_dif(int col1, int col2);
void				blinding_lights(t_env *e);

#endif
