/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 14:45:49 by lgorilla          #+#    #+#             */
/*   Updated: 2020/06/22 14:52:28 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char*)str;
	if (ch == '\0')
	{
		while (ptr[i])
			i++;
		return (ptr + i);
	}
	while (ptr[i] != '\0')
	{
		if (ptr[i] == ch)
			return (ptr + i);
		i++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		j;

	j = 0;
	i = 0;
	if (!dst)
		return (0);
	while (src[j] != '\0')
		j++;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i] != '\0')
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	char			*str;

	if (!s2)
		return (NULL);
	if (s1 == NULL)
		s1_len = 0;
	else
	{
		s1_len = 0;
		while (s1[s1_len] != '\0')
			s1_len++;
	}
	s2_len = 0;
	while (s2[s2_len] != '\0')
		s2_len++;
	if (!(str = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	if (s1 != NULL)
		ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(str + s1_len, s2, s2_len + 1);
	return (str);
}
