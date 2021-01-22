/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:18:26 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/09 20:46:48 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*num_fin(int i, int n, int sign, char *str)
{
	while (i-- - sign)
	{
		if (n < 0)
		{
			str[0] = '-';
			n = -n;
		}
		str[i] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	char	*num_str;
	int		i;
	int		num;
	int		sign;

	num_str = "-2147483648";
	i = 0;
	if (n == -2147483648)
		return (ft_strdup(num_str));
	sign = (n < 0) ? 1 : 0;
	num = n;
	while (num / 10)
	{
		num = num / 10;
		i++;
	}
	i += (n < 0) ? 2 : 1;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	num_fin(i, n, sign, str);
	return (str);
}
