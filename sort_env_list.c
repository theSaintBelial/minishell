/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:48:49 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/10 18:48:59 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_str_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;	
}

void	ft_int_swap(int *n1, int *n2)
{
	int tmp;

	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

void	sort_env_list(t_env *env)
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
				ft_int_swap(&(tmp1->visible), &(tmp1->next->visible));
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
}
