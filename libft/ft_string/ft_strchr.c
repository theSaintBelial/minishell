/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:44:21 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:16:53 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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
