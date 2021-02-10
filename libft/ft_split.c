/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 20:16:18 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/09 18:37:41 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		count_word(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i])
	{
		while (s[i])
		{
			if (s[i] != c)
			{
				while (s[i] && s[i] != c)
					i++;
				count++;
			}
			else
				i++;
		}
	}
	return (count);
}

static int		word_l(const char *s, int i, char c, int word_len)
{
	word_len = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (word_len);
		i++;
		word_len++;
	}
	return (word_len);
}

static void		mem(int *j, char **ptr, const char *s, int *word_len)
{
	if (!(ptr[*j] = (char *)malloc(sizeof(char) * (*word_len + 1))))
	{
		while (*j--)
			free(ptr[*j]);
		free(ptr);
		return ;
	}
	ft_strlcpy(ptr[*j], s, *word_len + 1);
	(*j)++;
}

static char		**split_words(char const *s, char c, char **ptr, int i)
{
	int		j;
	int		word_len;

	i = 0;
	word_len = 0;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i])
	{
		while (s[i])
		{
			if (s[i] != c)
			{
				word_len = word_l(s, i, c, word_len);
				mem(&j, ptr, s + i, &word_len);
				while (s[i] && s[i] != c)
					i++;
			}
			else
				i++;
		}
	}
	ptr[j] = NULL;
	return (ptr);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**ptr;

	i = 0;
	if (!s)
		return (NULL);
	count = count_word(s, c);
	if (!(ptr = (char**)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	if (!count)
	{
		*ptr = NULL;
		return (ptr);
	}
	split_words(s, c, ptr, i);
	return (ptr);
}
