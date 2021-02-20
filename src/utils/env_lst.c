/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:19:19 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/20 14:11:21 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_lst.h"
#include <ft_string.h>

/*
*  SORT LIST FUNC IN env_lst_sort.c
*/

t_env	*env_lst_new(char *name, char *value, bool visible)
{
	t_env *tmp;

	tmp = (t_env*)malloc(sizeof(t_env));
	if (tmp != NULL)
	{
		tmp->name = name;
		tmp->value = value;
		tmp->visible = visible;
		tmp->next = NULL;
	}
	return (tmp);
}

t_env	*env_lst_dup(t_env *envlst)
{
	t_env	*newlst;
	t_env	*tmp;
	t_env 	*cur;

	newlst = NULL;
	tmp = envlst;
	while (tmp)
	{
		cur = env_lst_new(ft_strdup(tmp->name), ft_strdup(tmp->value), tmp->visible);
		env_lst_add_back(&newlst, cur);
		tmp = tmp->next;
	}
	return (newlst);
}

void	env_lst_clear(t_env *env)
{
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		env_lst_clear(env->next);
		free(env);
	}
}

void	env_lst_add_back(t_env **lst, t_env *node)
{
	t_env *tmp;

	if (!lst || !node)
		return ;
	tmp = *lst;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
	else
		*lst = node;
}

void	env_lst_delone(t_env **env, char *name)
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

void	env_lst_create(t_env **env, char **envp)
{
	int		i;
	int		j;
	char	*s1;
	char	*s2;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j])
		{
			if (envp[i][j] == '=')
			{
				s1 = (char *)malloc(sizeof(char) * j + 1);
				ft_strlcpy(s1, envp[i], j + 1);
				s2 = (char *)malloc(sizeof(char) * ft_strlen(envp[i] + j));
				j++;
				ft_strlcpy(s2, envp[i] + j, ft_strlen(envp[i] + j));
				env_lst_add_back(env, env_lst_new(s1, s2, true));
				break ;
			}
		}
	}
}

t_env	*env_lst_find(t_env *envlst, char *data_ref)
{
	if (envlst)
	{
		while (envlst)
		{
			if (ft_strncmp(envlst->name, data_ref, 1024) == 0)
				return (envlst);
			envlst = envlst->next;
		}
	}
	return (NULL);
}
