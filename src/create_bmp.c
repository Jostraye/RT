/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 19:01:36 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/19 18:30:15 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_vc						hextorgb(int hex)
{
	t_vc rgb;

	rgb.x = (int)((hex / (0x100 * 0x100)) % 0x100);
	rgb.y = (int)((hex / 0x100) % 0x100);
	rgb.z = (int)(hex % 0x100);
	return (rgb);
}

static	unsigned char		*create_bmp_img(int *imgstr)
{
	unsigned char	*img;
	int				o;
	t_vc			rgb;

	if (!(img = (unsigned char*)malloc(sizeof(unsigned char) * 3 * 2 * WINY * WINZ)))
		return (0);
	ft_memset(img, 0, 3 * 2 * WINY * WINZ);
	o = 0;
	while (o < (WINY * WINZ))
	{
		rgb = hextorgb(imgstr[o]);
		img[o * 3 + 2] = (unsigned char)rgb.x;
		img[o * 3 + 1] = (unsigned char)rgb.y;
		img[o * 3 + 0] = (unsigned char)rgb.z;
		o++;
	}
	return (img);
}

static void					write_file_header(FILE *f)
{
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	int				filesize;

	filesize = 54 + 2 * WINY * WINZ;
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	fwrite(bmpfileheader, 1, 14, f);
}

static void					write_info_header(FILE *f)
{
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};

	bmpinfoheader[4] = (unsigned char)(WINY);
	bmpinfoheader[5] = (unsigned char)(WINY >> 8);
	bmpinfoheader[6] = (unsigned char)(WINY >>16);
	bmpinfoheader[7] = (unsigned char)(WINY >>24);
	bmpinfoheader[8] = (unsigned char)(WINZ);
	bmpinfoheader[9] = (unsigned char)(WINZ >> 8);
	bmpinfoheader[10] = (unsigned char)(WINZ >>16);
	bmpinfoheader[11] = (unsigned char)(WINZ >>24);
	fwrite(bmpinfoheader, 1, 40, f);
}

void	create_bmp_file(int *imgstr)
{
	FILE			*f;
	unsigned char	*img = NULL;
	unsigned char 	bmppad[3] = {0,0,0};
	int				i;

	if (!(img = create_bmp_img(imgstr)))
		return ;
	f = fopen("img.bmp","wb");
	i = -1;
	write_file_header(f);
	write_info_header(f);
	while (++i < WINZ)
	{
	    fwrite(img + (WINY * (WINZ - i - 1) * 3),3, WINY , f);
	    fwrite(bmppad,1,(4 - (WINY * 3) % 4) % 4 , f);
	}
	free(img);
	fclose(f);
}
