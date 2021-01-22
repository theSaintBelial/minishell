/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:19:38 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/20 12:10:31 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
