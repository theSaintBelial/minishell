/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:21:55 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/18 11:55:42 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *str, size_t n)
{
	int				i;
	unsigned char	*ptr;
	unsigned char	*dst_ptr;

	i = 0;
	ptr = (unsigned char*)str;
	dst_ptr = (unsigned char*)dst;
	if (!n || dst == str)
		return (dst);
	while (n > 0)
	{
		dst_ptr[i] = ptr[i];
		i++;
		n--;
	}
	return (dst);
}
