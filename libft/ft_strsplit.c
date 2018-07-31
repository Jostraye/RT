/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:11:41 by tmervin           #+#    #+#             */
/*   Updated: 2018/04/09 11:31:08 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nb_words(char const *s, char c)
{
	int charzone;
	int i;
	int nb;

	i = 0;
	charzone = 0;
	nb = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			charzone = 0;
		else if (charzone == 0)
		{
			charzone = 1;
			nb++;
		}
		i++;
	}
	return (nb);
}

static char		*ft_create_word(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (!(word = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		i;
	int		n;
	int		charzone;

	if (!(split = (char**)malloc(sizeof(char*) * (ft_nb_words(s, c) + 1))))
		return (NULL);
	split[ft_nb_words(s, c)] = NULL;
	if (ft_nb_words(s, c) == 0)
		return (split);
	charzone = 0;
	i = -1;
	n = -1;
	while (s[++i] != '\0' && n < ft_nb_words(s, c))
	{
		if (s[i] == c)
			charzone = 0;
		else if (charzone == 0)
		{
			split[++n] = ft_create_word(&s[i], c);
			charzone = 1;
		}
	}
	return (split);
}
