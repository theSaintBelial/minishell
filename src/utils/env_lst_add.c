/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:48:49 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/18 20:08:08 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_lst.h"
#include <ft_string.h>
#include <ft_stdlib.h>
#include "minishell.h"
#include "errors.h"
#include "cmd.h"

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
	if (!envlst)
		return (NULL);
	if (!(env = (char *)ft_calloc(ft_strlen(envlst->name)
	+ ft_strlen(envlst->value) + 2, sizeof(char))))
		return (NULL);
	cur_sym = env + ft_strlcpy(env, envlst->name, ft_strlen(envlst->name) + 1);
	cur_sym += ft_strlcpy(cur_sym, "=", 2);
	ft_strlcpy(cur_sym, envlst->value, ft_strlen(envlst->value) + 1);
	return (env);
}

char	**env_lst_tostrarr(t_env *envlst, bool visible)
{
	char	**envp;
	int		i;

	i = 0;
	if (!(envp = (char **)ft_calloc(env_lst_len(envlst, visible)
	+ 1, sizeof(char *))))
		return (NULL);
	while (envlst)
	{
		if (envlst->visible == visible)
		{
			if (!(envp[i] = env_lst_node_to_str(envlst)))
				return (NULL);
			i++;
		}
		envlst = envlst->next;
	}
	return (envp);
}

char	*env_lst_getval(t_env *envlst, char *name)
{
	extern int	g_exit_code;
	t_env		*node;
	char		*value;

	value = NULL;
	if (!ft_strncmp(name, "?", 10))
	{
		if (!(value = ft_itoa(g_exit_code)))
			msg_exit(EXIT_FAILURE, "env_lst", ERR_MALLOC);
	}
	else if ((node = env_lst_find(envlst, name)))
	{
		if (!(value = ft_strdup(node->value)))
			msg_exit(EXIT_FAILURE, "env_lst", ERR_MALLOC);
		return (value);
	}
	else
		return (NULL);
	return (value);
}

void	env_lst_set(t_env *envlst, char *set, bool visible)
{
	char	**env_var;
	char	*data;
	t_env	*env;

	if (set)
	{
		if (!(env_var = ft_split(set, '=')))
			msg_exit(EXIT_FAILURE, "env_lst", "Malloc error");
		if ((env = env_lst_find(envlst, env_var[0])))
		{
			data = env->value;
			env->value = env_var[1];
			free(data);
			free(env_var[0]);
		}
		else
		{
			if (!(env = env_lst_new(env_var[0], env_var[1], visible)))
				msg_exit(EXIT_FAILURE, "env_lst", "Malloc error");
			env_lst_add_back(&envlst, env);
		}
		free(env_var);
	}
}
