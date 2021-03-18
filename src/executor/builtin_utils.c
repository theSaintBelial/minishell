/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:28:45 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 20:29:14 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <ft_string.h>
#include <ft_stdio.h>
#include "env_lst.h"
#include "errors.h"

extern t_env	*g_envlst;
extern int		g_exit_code;

void			export_exec(t_cmd *cmd)
{
	t_env	*cpy;
	t_env	*tmp;
	int		i;

	if (cmd->argc == 1)
	{
		if (!(cpy = env_lst_dup(g_envlst)))
			msg_exit(EXIT_FAILURE, "export", "Malloc error");
		env_lst_sort(cpy);
		print_env_lst(cpy, true);
		env_lst_clear(cpy);
	}
	else
	{
		i = -1;
		while (cmd->argv[++i])
			if (ft_strchr(cmd->argv[i], '='))
				env_lst_set(g_envlst, cmd->argv[i], true);
			else if ((tmp = env_lst_find(g_envlst, cmd->argv[i])))
				tmp->visible = true;
	}
	g_exit_code = EXIT_SUCCESS;
}

void			unset_exec(t_cmd *cmd)
{
	int		i;

	if (cmd->argc > 1)
	{
		i = 1;
		while (cmd->argv[i])
		{
			env_lst_delone(&g_envlst, cmd->argv[i]);
			i++;
		}
	}
	g_exit_code = EXIT_SUCCESS;
}

void			env_exec(t_cmd *cmd)
{
	if (cmd->argc > 1)
		msg_return(EXIT_FAILURE, "env", "Too many arguments");
	else
	{
		print_env_lst(g_envlst, false);
		g_exit_code = EXIT_SUCCESS;
	}
}
