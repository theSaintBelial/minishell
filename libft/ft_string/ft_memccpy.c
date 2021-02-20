/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:19:38 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:16:50 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memccpy(void *dst, const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*dst_ptr;

	i = 0;
	ptr = (unsigned char*)str;
	dst_ptr = (unsigned char*)dst;
	while (i < n)
	{
		dst_ptr[i] = ptr[i];
		if (ptr[i] == (unsigned char)c)
		{
			return (dst + i + 1);
		}
		i++;
	}
	return (NULL);
}
