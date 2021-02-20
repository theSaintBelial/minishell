/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:53:17 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:07:46 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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
