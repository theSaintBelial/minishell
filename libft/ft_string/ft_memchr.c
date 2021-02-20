/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:20:16 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:16:51 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
		{
			return ((unsigned char*)src + i);
		}
		i++;
	}
	return (NULL);
}
