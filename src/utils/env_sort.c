/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:05:13 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 20:07:33 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_lst.h"
#include <ft_string.h>

void	ft_str_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	ft_int_swap(int *n1, int *n2)
{
	int		tmp;

	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

void	env_lst_sort(t_env *env)
{
	t_env *tmp;
	t_env *tmp1;

	tmp = env;
	while (tmp && tmp->next)
	{
		tmp1 = env;
		while (tmp1->next)
		{
			if (ft_strncmp(tmp1->name, tmp1->next->name, 1000) > 0)
			{
				ft_str_swap(&(tmp1->name), &(tmp1->next->name));
				ft_str_swap(&(tmp1->value), &(tmp1->next->value));
				ft_int_swap((int *)&(tmp1->visible),
				(int *)&(tmp1->next->visible));
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
}
