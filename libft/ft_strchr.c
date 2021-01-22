/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:44:21 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/20 14:45:08 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
