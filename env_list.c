/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:19:19 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/10 18:50:27 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
*  SORT LIST FUNC IN sort_env_list.c
*/

t_env	*new_lst(char *data, char *value)
{
	t_env *tmp;

	tmp = (t_env*)malloc(sizeof(t_env));
	if (tmp != NULL)
	{
		tmp->name = data;
		tmp->value = value;
		tmp->visible = TRUE;
		tmp->next = NULL;
	}
	return (tmp);
}

void	del_env_lst(t_env *env)
{
	while (env)
	{
		free(env->name);
		free(env->value);
		del_env_lst(env->next);
		free(env);
	}
}


void	env_list_add_back(t_env **lst, t_env *new)
{
	t_env *tmp;

	if (!lst || !new)
		return ;
	tmp = *lst;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

void	del_one_lst(t_env **env, char *name)
{
	t_env *tmp;
	t_env *tmp2;
	t_env *tmp3;

	tmp = *env;
	if (name == NULL)
		return ;
	while (tmp)
	{
		if (ft_strncmp(name, tmp->name, ft_strlen(tmp->name)) == 0)
		{
			tmp3 = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			tmp = tmp2;
			tmp->next = tmp3;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}

void	envp_create_lst(t_env **env)
{
	int		i;
	int		j;
	char	*s1;
	char	*s2;

	i = 0;
	while (g_envp[i])
	{
		j = 0;
		while (g_envp[i][j])
		{
			if (g_envp[i][j] == '=')
			{
				s1 = (char *)malloc(sizeof(char) * j + 1);
				ft_strlcpy(s1, g_envp[i], j + 1);
				s2 = (char *)malloc(sizeof(char) * ft_strlen(g_envp[i] + j));
				ft_strlcpy(s2, g_envp[i] + ++j, ft_strlen(g_envp[i] + j));
				env_list_add_back(env, new_lst(s1, s2));
				break ;
			}
			j++;
		}
		i++;
	}
}