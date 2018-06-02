#include "rtv1.h"
#include "mlx.h"
#include <stdio.h>

int	get_nb_line(char *file_name)
{
	int		fd;
	int		nb_line;
	char *str;

	nb_line = 0;
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (0);

	while (get_next_line(fd, &str))
	{
		if (str[0] != '#')
			nb_line++;
	}
	return (nb_line);
}

int	get_nb_points(char *line)
{
	int nb_points;
	int	nombre;

	nb_points = 0;
	nombre = 0;
	while (line[0])
	{
		if (line[0] && line[0] != ' ' && !nombre)
		{
			nombre = 1;
			nb_points++;
		}
		else if (line[0] && line[0] == ' ')
			nombre = 0;
		line++;
	}
	return (nb_points);
}

int check_name(char *str)
{
	if (strcmp(str, "sphere") && strcmp(str, "cylindre") && strcmp(str, "plane")
&& strcmp(str, "cone") && strcmp(str, "eye") && strcmp(str, "spot"))
		return (1);
	return (0);
}

int ft_htod(char c)
{
	if (ft_isdigit(c))
		return ((int)(c - 48));
	else if ('A' <= 'c' && 'F' >= c)
		return ((int)(c - 55));
	else if ('a' <= c && 'f' >= c)
 		return ((int)(c - 87));
	else
		return (-1);
}

int ft_htoi(char *str)
{
	int i;
	int color;

	color = 0;
	i = 2;
	while (str[0] != '0' && (str[1] != 'x' || str[1] != 'X'))
		return (-1);
	while (str[i])
	{
		if (ft_htod(str[i]) >= 0)
		{
			color = ft_htod(str[i]) + color * 16;
		}
		i++;
	}
	return (color);
}

int ft_iscolor(char *str)
{
	int color;

	color = ft_htoi(str);
	if (color < 0 || color > 0xFFFFFF)
		return (1);
	else
		return (0);
}

int ft_isnumber(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '-' || str[i] == '+') && i == 0)
			i++;
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int check_value(char **str)
{
  int i;
	int j;

  i = 0;
	j = 3;
	while (str[i])
		i++;
	if (i != 9)
		return (1);
	if (check_name(str[0]))
		return (2);
	if (ft_iscolor(str[1]))
		return (3);
	if (ft_isnumber(str[2]) || ft_atoi(str[2]) < 0)
		return (4);
	while (j < i)
	{
		if (ft_isnumber(str[j]) || ft_atoi(str[j]) < -70000)
			return (5);
		j++;
	}
	return (0);
}

int check_light(char **str)
{
  int i;
	int j;

  i = 0;
	j = 1;
	while (str[i])
		i++;
	if ((i != 4 && ft_strcmp(str[0], "eye")) ||
	(i != 7 && ft_strcmp(str[0], "spot")))
		return (1);
	while (j < i)
	{
		if (ft_isnumber(str[j]) || atoi(str[j]) < -2147483648 || atoi(str[j]) > 2147483647)
			return (5);
		j++;
	}
	return (0);
}

t_object attribute_light(char **tab_values)
{
	t_object scene;

	scene.where.x = check_light(tab_values);
	scene.what.shape = "invalid object";
	if (scene.where.x > 0)
		return (scene);
	scene.what.shape = tab_values[0];
	scene.where.x = (double)ft_atoi(tab_values[1]);
	scene.where.y = (double)ft_atoi(tab_values[2]);
	scene.where.z = (double)ft_atoi(tab_values[3]);
	if (strcmp(scene.what.shape,"spot"))
	{
		scene.direct.x = (double)ft_atoi(tab_values[4]);
		scene.direct.y = (double)ft_atoi(tab_values[5]);
		scene.direct.z = (double)ft_atoi(tab_values[6]);
	}
	return (scene);
}

t_object attribute_object(char **tab_values)
{
	t_object scene;

	scene.where.x = check_value(tab_values);
	scene.what.shape = "invalid object";
	if (scene.where.x > 0)
		return (scene);
	scene.what.shape = tab_values[0];
	scene.what.color = ft_htoi(tab_values[1]);
	scene.what.length = (double)ft_atoi(tab_values[2]);
	scene.where.x = (double)ft_atoi(tab_values[3]);
	scene.where.y = (double)ft_atoi(tab_values[4]);
	scene.where.z = (double)ft_atoi(tab_values[5]);
	scene.direct.x = (double)ft_atoi(tab_values[6]);
	scene.direct.y = (double)ft_atoi(tab_values[7]);
	scene.direct.z = (double)ft_atoi(tab_values[8]);
	return (scene);
}

char *tabtospace(char *str)
{
	int j;

	j = -1;
	while (str[++j])
	{
		if (str[j] == '\t')
			str[j] = ' ';
		j++;
	}
	return (str);
}

t_object *attribute_scene(t_object *scene, int fd)
{
	int		i;
	char	*str;
	char **tab_values;

	i = 0;
	while (get_next_line(fd, &str))
	{
		if (str[0] != '#')
		{
			str = tabtospace(str);
			tab_values = ft_strsplit(str, ' ');
			if (ft_strcmp(tab_values[0], "eye") && ft_strcmp(tab_values[0],"spot"))
				scene[i] = attribute_object(tab_values);
			else
				scene[i] = attribute_light(tab_values);
			i++;
		}
	}
	return (scene);
}

t_object *error_messages(int nb_line, t_object *scene)
{
	int i;

	i = 0;
	while (i < nb_line)
	{
		if (ft_strcmp(scene[i].what.shape, "invalid object"))
			i++;
		else
		{
			if (scene[i].where.x == 1)
				printf("Some objects do not have good amount of attributes\n");
			if (scene[i].where.x == 2)
				printf("Some objects have an unknown name\n Choose from :\n- eye\n- spot\n- sphere\n- cylindre\n- plane\n- cone\n");
			if (scene[i].where.x == 3)
				printf("Some objects have an invalid color\nColors must be written in hexadecimal format and not exceed max value 0XFFFFFF\n");
			if (scene[i].where.x == 4)
				printf("Some objects length is invalid (careful : must be positive)\n");
			if (scene[i].where.x == 5)
				printf("Some objects coordinates are invalid\n");
			return (NULL);
		}
	}
	return (scene);
}

t_object *get_scene(char **argv)
{
	int			fd;
	int			nb_line;
	t_object			*scene;

	if (argv == NULL)
		return (NULL);
	if ((nb_line = get_nb_line(argv[1])) == 0)
	{
		printf("The configuration file is empty\n");
		return (NULL);
	}
	if (!(scene = (t_object *)malloc(sizeof(t_object) * (nb_line + 1))))
		return (NULL);
	if ((fd = open(argv[1], O_RDONLY)) >= 0 && nb_line > 0)
		scene = attribute_scene(scene, fd);
	scene = error_messages(nb_line, scene);
	return (scene);
}
