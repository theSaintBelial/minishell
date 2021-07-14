/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:21:55 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:08:00 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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
