/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 18:25:04 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/20 15:56:42 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	replace_char(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str) && !ft_isdigit(*str))
			*str = ' ';
		str++;
	}
}

int		*get_xpm_size(char *file)
{
	int		fd;
	int		line;
	int		*wh;
	char	*str;
	char	**split;

	fd = open(file, O_RDONLY);
	line = 0;
	if (!(wh = (int *)malloc(sizeof(int) * 2)))
		return (NULL);
	if (fd < 0)
		return (0);
	while (get_next_line(fd, &str) == 1 && line <= 4)
	{
		line++;
		if (line == 4)
		{
			replace_char(str);
			split = ft_strsplit(str, ' ');
			wh[0] = ft_atoi(split[0]);
			wh[1] = ft_atoi(split[1]);
			free_split(split);
			free(str);
			return (wh);
		}
		free(str);
	}
	free(str);
	return (NULL);
}

int		**create_color_tab(int *imgstr, int *size)
{
	int		**color_tab;
	int		x;
	int		y;
	int		i;

	y = 0;
	i = 0;
	if (!(color_tab = (int **)malloc(sizeof(int*) * size[1])))
		return (NULL);
	while (y < size[1])
	{
		if (!(color_tab[y] = (int *)malloc(sizeof(int) * size[0])))
			return (NULL);
		x = 0;
		while (x < size[0])
		{
			color_tab[y][x] = imgstr[i];
			x++;
			i++;
		}
		y++;
	}
	return (color_tab);
}

int		load_texture_to_obj(t_obj *obj)
{
	void	*image;
	void	*mlx;
	int		*imgstr;
	int		*size;
	int 	bpp;
	int 	s_l;
	int 	endian;

	if (!(obj->texture_size = get_xpm_size("src/earth.xpm")))
		return (0);
	size = get_xpm_size("src/earth.xpm");
	mlx = mlx_init();
	image = mlx_xpm_file_to_image(mlx, "src/earth.xpm", &size[0], &size[1]);
	imgstr = (int *)mlx_get_data_addr(image, &bpp, &s_l, &endian);
	if (!(obj->texture_tab = create_color_tab(imgstr, obj->texture_size)))
		return (0);
	return (1);
}
