/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:02:18 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 20:07:17 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_lst.h"
#include <ft_string.h>
#include "minishell.h"
#include "errors.h"

bool	env_lst_delone(t_env **env, char *name)
{
	t_env *tmp;
	t_env *tmp2;
	t_env *tmp3;

	tmp = *env;
	if (name == NULL)
		return (false);
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
			return (true);
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
	return (false);
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

void	print_env_lst(t_env *envlst, bool visible)
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
