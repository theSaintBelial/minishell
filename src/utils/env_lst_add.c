/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thesaintbelial <thesaintbelial@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:48:49 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/07 09:42:14 by thesaintbel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_lst.h"
#include <ft_string.h>
#include <ft_stdlib.h>
#include "minishell.h"
#include "errors.h"

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
				ft_int_swap((int *)&(tmp1->visible), (int *)&(tmp1->next->visible));
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
}

size_t	env_lst_len(t_env *env, bool visible)
{
	size_t	len;

	len = 0;
	while (env)
	{
		if (env->visible == visible)
			len++;
		env = env->next;
	}
	return (len);
}

char	*env_lst_node_to_str(t_env *envlst)
{
	char	*env;
	char	*cur_sym;

	env = NULL;
	if (envlst)
	{
		env = (char *)ft_calloc(ft_strlen(envlst->name) + ft_strlen(envlst->value) + 2, sizeof(char));
		cur_sym = env;
		if (env)
		{
			cur_sym += ft_strlcpy(env, envlst->name, ft_strlen(envlst->name) + 1);
			cur_sym += ft_strlcpy(cur_sym, "=", 2);
			ft_strlcpy(cur_sym, envlst->value, ft_strlen(envlst->value) + 1);
		}
	}
	return (env);
}

char	**env_lst_tostrarr(t_env *envlst, bool visible)
{
	char	**envp;
	int		i;

	i = 0;
	envp = (char **)ft_calloc(env_lst_len(envlst, visible) + 1, sizeof(char *));
	if (envp)
	{
		while (envlst)
		{
			if (envlst->visible == visible)
			{
				envp[i] = env_lst_node_to_str(envlst);
				i++;
			}
			envlst = envlst->next;
		}
	}
	return (envp);
}

char	*env_lst_getval(t_env *envlst, char *name)
{
	extern int	g_exit_code;
	t_env		*node;
	char		*value;

	if (!ft_strncmp(name, "?", 10))
	{
		if (!(value = ft_itoa(g_exit_code)))
			msg_exit(EXIT_FAILURE, "env_lst", "Malloc error");
	}
	else
		value = ((node = env_lst_find(envlst, name)) ? ft_strdup(node->value) : NULL);
	return (value);
}

void	env_lst_set(t_env *envlst, char *set, bool visible)
{
	char	**env_var;
	t_env	*env;

	if (set)
	{
		if (!(env_var = ft_split(set, '=')))
			msg_exit(EXIT_FAILURE, "env_lst", "Malloc error");
		if ((env = env_lst_find(envlst, env_var[0])))
			env->value = env_var[1];
		else
		{
			if (!(env = env_lst_new(env_var[0], env_var[1], visible)))
				msg_exit(EXIT_FAILURE, "env_lst", "Malloc error");
			env_lst_add_back(&envlst, env);
		}
	}
}

void 	print_env_lst(t_env *envlst, bool visible)
{
	t_env	*tmp;

	tmp = envlst;
	while (tmp)
	{
		if (!visible || tmp->visible)
		{
			if (visible)
				ft_putstr_fd("export ", STDOUT_FILENO);
			ft_putstr_fd(tmp->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(tmp->value, STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
}
