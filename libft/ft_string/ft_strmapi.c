/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:49:42 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:07:21 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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
