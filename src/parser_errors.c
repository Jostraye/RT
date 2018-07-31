/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:11:50 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/12 15:59:35 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	error_messages(int error)
{
	if (error == 1)
		exit_message("Some objects do not have good amount of attributes\n");
	if (error == 2)
		exit_message("Some objects have an unknown name\n Choose from :\n\
		- eye\n- light\n- sphere\n- cylinder\n- plane\n- cone\n");
	if (error == 3)
		exit_message("Some objects have an invalid color:\n\
		Colors must be written in hexadecimal format\n\
		Colors must not exceed max value 0xFFFFFF\n");
	if (error == 4)
		exit_message("Some objects length is invalid\n\
		(Careful : must be positive)\n");
	if (error == 5)
		exit_message("Some objects coordinates are invalid\n");
	if (error == 6)
		exit_message("Eye definition is mandatory (only one)\n");
	if (error == 7)
		exit_message("Diffuse, ambiant and specular must be [0.0 - 1.0] !\n");
}

int		check_value(char **str)
{
	int i;
	int type;

	i = -1;
	type = name_type(str[0]);
	if (!type)
		return (2);
	while (str[++i])
	{
		if ((ft_isnumber(str[i]) && i > 0) && (ft_isnumber(str[i]) && i < 7))
			return (5);
	}
	if ((type > 2 && i != 15) || (type == 1 && i != 8) || (type == 2 && i != 7))
		return (1);
	if (type > 2)
	{
		if (ft_atof(str[9]) == -1.0 || ft_atof(str[10]) == -1.0
		|| ft_atof(str[11]) == -1.0 || ft_atof(str[13]) == -1.0)
			return (7);
		if (ft_iscolor(str[7]))
			return (3);
		if (ft_atoi(str[8]) < 0.0)
			return (4);
	}
	return (0);
}

char	*tabtospace(char *str)
{
	int j;

	j = -1;
	while (str[++j])
	{
		if (str[j] == '\t')
			str[j] = ' ';
	}
	return (str);
}
