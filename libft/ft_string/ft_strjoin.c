/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:46:36 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:07:42 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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
