/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:47:28 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:07:05 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dst_len;
	size_t fin;
	size_t src_len;

	dst_len = 0;
	while (dst[dst_len] != '\0')
		dst_len++;
	fin = 0;
	while (src[fin] != '\0')
		fin++;
	if (size <= dst_len)
		fin = size + fin;
	else
		fin = dst_len + fin;
	src_len = 0;
	while (src[src_len] != '\0' && dst_len + 1 < size)
	{
		dst[dst_len] = src[src_len];
		dst_len++;
		src_len++;
	}
	dst[dst_len] = '\0';
	return (fin);
}
