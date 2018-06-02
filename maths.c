#include "rtv1.h"
#define DST_IMG 1000
#define ANGL_CVRT 0.0174532925


t_vect matrix_mult(t_vect a, t_matrix b)
{
	t_vect c;
	c.x = a.x * b.xa + a.y * b.xb + a.z * b.xc;
	c.y = a.x * b.ya + a.y * b.yb + a.z * b.yc;
	c.z = a.x * b.za + a.y * b.zb + a.z * b.zc;
	return (c);
}

t_vect vect_mult(double a, t_vect V)
{
	V.x = V.x * a;
	V.y = V.y * a;
	V.z = V.z * a;
	return (V);
}

t_matrix rotate_matrix(t_vect a)
{
	t_matrix shear;

	a = vect_mult((double)ANGL_CVRT, a);

	shear.xa = cos(a.y) * cos(a.z);
	shear.xb = - cos(a.y) * sin(a.z);
	shear.xc = sin(a.y);
	shear.ya = sin(a.x) * sin(a.y) * cos(a.z) + cos(a.x) * sin(a.z);
	shear.yb = - sin(a.x) * sin(a.y) * sin(a.z) + cos(a.x) * cos(a.z);
	shear.yc = - sin(a.x) * cos(a.y);
	shear.za = - cos(a.x) * sin(a.y) * cos(a.z) + sin(a.x) * sin(a.z);
	shear.zb = cos(a.x) * sin(a.y) * sin(a.z) + sin(a.x) * cos(a.z);
	shear.zc = cos(a.x) * cos(a.y);
	return(shear);
}

// t_matrix rotate_matrix(t_vect a)
// {
// 	t_matrix shear;
//
// 	a = vect_mult((double)ANGL_CVRT, a);
//
// 	shear.xa = cos(a.z);
// 	shear.xb = -sin(a.z);
// 	shear.xc = 0;
// 	shear.ya = sin(a.z);
// 	shear.yb = cos(a.z);
// 	shear.yc = 0;
// 	shear.za = 0;
// 	shear.zb = 0;
// 	shear.zc = 1;
// 	return(shear);
// }
// t_matrix inverse_matrix(t_vect a)
// {
// 	t_matrix shear;
//
// 	a = vect_mult((double)(-ANGL_CVRT), a);
//
// 		shear.xa = cos(a.z);
// 		shear.xb = -sin(a.z);
// 		shear.xc = 0;
// 		shear.ya = sin(a.z);
// 		shear.yb = cos(a.z);
// 		shear.yc = 0;
// 		shear.za = 0;
// 		shear.zb = 0;
// 		shear.zc = 1;
// 	return(shear);
// }

t_matrix inverse_matrix(t_vect a)
{
	t_matrix shear;

	a = vect_mult((double)(ANGL_CVRT), a);

	shear.xa = cos(-a.y) * cos(-a.z);
	shear.xb = - cos(-a.x) * sin(-a.z) + sin(-a.x) * sin(-a.y) * cos(-a.z);
	shear.xc = sin(-a.x) * sin(-a.y) + cos(-a.x) * sin(-a.y) * cos(-a.z);
	shear.ya = cos(-a.y) * sin(-a.z);
	shear.yb = cos(-a.x) * cos(-a.z) + sin(-a.x) * sin(-a.y) * sin(-a.z);
	shear.yc = - sin(-a.x) * cos(-a.z) + cos(-a.x) * sin(-a.y) * sin(-a.z);
	shear.za = - sin(-a.y);
	shear.zb = sin(-a.x) * cos(-a.y);
	shear.zc = cos(-a.x) * cos(-a.y);
	return(shear);
}

// t_matrix rotate_matrix(t_vect a)
// {
// 	t_matrix shear;
//
// 	a = vect_mult((double)ANGL_CVRT, a);
//
// 	shear.xa = 1;
// 	shear.xb = 0;
// 	shear.xc = 0;
// 	shear.ya = 0;
// 	shear.yb = cos(a.x);
// 	shear.yc = sin(a.x);
// 	shear.za = 0;
// 	shear.zb = -sin(a.x);
// 	shear.zc = cos(a.x);
// 	return(shear);
// }

t_vect	vect_bind(t_vect a, t_vect b)
{
	t_vect c;
	c.x = b.x - a.x;
	c.y = b.y - a.y;
	c.z = b.z - a.z;
	return (c);
}

t_vect	vect_add(t_vect a, t_vect b)
{
	t_vect c;
	c.x = b.x + a.x;
	c.y = b.y + a.y;
	c.z = b.z + a.z;
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
int ft_sign(double a)
{
    if (a < 0)
      return (-1);
    else
      return (1);
}

double delta_calc(t_vect A)
{
	return((double)(A.y * A.y) - (double)(4.0 * A.x * A.z));
}
