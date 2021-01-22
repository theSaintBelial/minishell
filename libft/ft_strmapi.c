/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:49:42 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/20 13:16:06 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		s_len;
	int		j;

	if (!s || !f)
		return (NULL);
	j = 0;
	s_len = ft_strlen(s);
	if (!(str = (char*)malloc(sizeof(char) * (s_len + 1))))
		return (NULL);
	while (s[j])
	{
		str[j] = (*f)(j, s[j]);
		j++;
	}
	str[j] = '\0';
	return (str);
}
