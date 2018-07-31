/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 10:45:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/06 15:22:00 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char			*cut_until(char *s, char c)
{
	char	*ret;
	int		i;
	int		l;

	if (!s)
		return (NULL);
	l = 0;
	while (s[l] && s[l] != c)
		l++;
	if ((ret = (char*)malloc(sizeof(char) * (l + 1))) == NULL)
		return (NULL);
	i = -1;
	while (++i < l)
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}

static t_list	*get_fd(const int fd, t_list **stock)
{
	t_list *ret;

	ret = *stock;
	while (ret)
	{
		if ((int)ret->content_size == fd)
			return (ret);
		ret = ret->next;
	}
	if (!(ret = ft_lstnew("\0", fd)))
		return (NULL);
	ft_lstadd(stock, ret);
	return (ret);
}

char			*reader(const int fd, t_list *t)
{
	int		ret;
	char	*tmp;
	char	*str;
	char	b[BUFF_SIZE + 1];

	str = t->content;
	while ((ret = read(fd, &b, BUFF_SIZE)))
	{
		b[ret] = '\0';
		tmp = str;
		str = ft_strjoin(str, b);
		free(tmp);
		if (ft_strchr(b, '\n'))
			break ;
	}
	return (str);
}

char			*cut_after(char *tempo)
{
	char *tmp2;

	tmp2 = ft_strchr(tempo, '\n');
	if (tmp2)
		tempo = ft_strdup(tmp2 + 1);
	else
		tempo = ft_strdup("\0");
	return (tempo);
}

int				get_next_line(const int fd, char **line)
{
	char			b[1];
	char			*tmp;
	static t_list	*stock = NULL;
	t_list			*tamp;

	if (fd < 0 || line == NULL || read(fd, &b, 0) < 0)
		return (-1);
	if (!(*line = ft_strnew(1)))
		return (-1);
	if (!(tamp = get_fd(fd, &stock)))
		return (-1);
	tamp->content = reader(fd, tamp);
	tmp = tamp->content;
	if (!**line && !*tmp)
		return (0);
	tmp = *line;
	*line = cut_until(tamp->content, '\n');
	free(tmp);
	tmp = tamp->content;
	tamp->content = cut_after(tamp->content);
	free(tmp);
	return (1);
}
