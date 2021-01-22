/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:53:17 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/11 12:00:31 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)str;
	if (ptr[i] == '\0' && ch == '\0')
		return (ptr + i);
	while (ptr[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (ptr[i] == ch)
			return (ptr + i);
		i--;
	}
	return (NULL);
}
