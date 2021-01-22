/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:22:59 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/09 20:46:13 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
