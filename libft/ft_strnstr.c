/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 20:16:18 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/23 13:32:51 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	len_lit;

	if (*little == '\0')
		return ((char*)big);
	len_lit = ft_strlen(little);
	if (ft_strlen(big) < len_lit || n < len_lit)
		return (NULL);
	i = 0;
	while (i < n && big[i] && len_lit + i <= n)
	{
		if (!ft_strncmp(big + i, little, len_lit))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
