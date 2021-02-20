/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:10:09 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:32:57 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"

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
