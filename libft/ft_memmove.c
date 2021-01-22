/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:22:26 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/20 14:37:03 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
