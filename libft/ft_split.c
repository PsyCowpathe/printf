/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:56:10 by agirona           #+#    #+#             */
/*   Updated: 2020/12/04 07:39:21 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_word(char *str, char c)
{
	int		i;
	int		find;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		find = 0;
		while ((str[i] == c) && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			i++;
			find = 1;
		}
		count = count + find;
	}
	return (count);
}

static int		get_word_length(char *str, char c, int i)
{
	int		len;

	len = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char		**ft_free(int i, char **res)
{
	while (i != 0)
	{
		free(res[i]);
		res[i] = NULL;
		i--;
	}
	res = NULL;
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	int		word;
	int		i;
	int		j;
	int		l;
	char	**res;

	j = 0;
	l = 0;
	word = count_word((char *)s, c);
	if (!s || !(res = malloc(sizeof(char *) * (word + 1))))
		return (0);
	while (l < word)
	{
		i = 0;
		while (s[j] == c)
			j++;
		if (!(res[l] = (char *)malloc(sizeof(char)
		* (get_word_length((char *)s, c, j) + 1))))
			return (ft_free(l, res));
		while (s[j] != c && s[j])
			res[l][i++] = s[j++];
		res[l++][i] = '\0';
	}
	res[l] = NULL;
	return (res);
}
