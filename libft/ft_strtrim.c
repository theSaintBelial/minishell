/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:56:31 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/13 11:08:27 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*mloc(char const *s1, int start, int s1_len)
{
	char *ptr;

	if (!(ptr = (char *)malloc(sizeof(char) * (s1_len + 1))))
		return (NULL);
	ft_strlcpy(ptr, s1 + start, s1_len + 1);
	ptr[s1_len] = '\0';
	return (ptr);
}

static char		*indx(char const *s1, char const *set, int start, int s2_len)
{
	int		j;
	int		s1_len;
	char	*str;

	while (s1[start])
	{
		j = 0;
		while (set[j] && s1[start] != set[j])
			j++;
		if (j == s2_len)
			break ;
		start++;
	}
	s1_len = ft_strlen(s1 + start);
	while (s1_len--)
	{
		j = 0;
		while (set[j] && s1[start + s1_len] != set[j])
			j++;
		if (j == s2_len)
			break ;
	}
	s1_len++;
	str = mloc(s1, start, s1_len);
	return (str);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		s2_len;
	int		start;
	char	*ptr;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char*)s1);
	s2_len = ft_strlen(set);
	start = 0;
	ptr = indx(s1, set, start, s2_len);
	return (ptr);
}
