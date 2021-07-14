/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:22:59 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:08:06 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;
	int				j;

	if (!n)
		return (str);
	j = 0;
	ptr = (unsigned char*)str;
	while (n > 0)
	{
		ptr[j] = (unsigned char)c;
		j++;
		n--;
	}
	return (str);
}
