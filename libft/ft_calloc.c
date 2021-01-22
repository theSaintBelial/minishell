/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:10:09 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/18 12:37:47 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void *get_mem;

	if ((get_mem = malloc(size * num)))
	{
		ft_bzero(get_mem, size * num);
		return (get_mem);
	}
	return (0);
}
