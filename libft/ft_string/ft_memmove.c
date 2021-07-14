/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:22:26 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:16:52 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr_dst;
	size_t			len;

	if (!dst && !src && n)
		return (NULL);
	ptr = (unsigned char*)src;
	ptr_dst = (unsigned char*)dst;
	len = n;
	if (ptr_dst < ptr)
	{
		while (n--)
			*ptr_dst++ = *ptr++;
	}
	else
	{
		while (n--)
		{
			ptr_dst[len - 1] = ptr[len - 1];
			len--;
		}
	}
	return (dst);
}
