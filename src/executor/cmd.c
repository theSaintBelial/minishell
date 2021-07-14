/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:17:07 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 22:08:47 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "parser.h"
#include "env_lst.h"
#include <ft_string.h>
#include <ft_stdlib.h>
#include "builtin.h"
#include "executor.h"

extern t_env	*g_envlst;
extern int		g_exit_code;

void			free_argv(char ***argv)
{
	int		i;
	char	**tmp;

	if (argv && *argv)
	{
		tmp = *argv;
		i = 0;
		while (tmp[i])
		{
			free(tmp[i]);
			i++;
		}
		free(*argv);
		*argv = NULL;
	}
}

char			**create_cmd(t_ast_tree *root_ptr, int *argc)
{
	t_ast_tree	*tmp;
	char		**argv;
	size_t		i;
	char		*data;

	if (!root_ptr || !(argv = (char **)ft_calloc(*argc + 1, sizeof(char *))))
		return (NULL);
	tmp = root_ptr;
	i = 0;
	while (tmp)
	{
		if (tmp->type == VARIABLE_N)
			data = env_lst_getval(g_envlst, tmp->data);
		else if (!(data = ft_strdup(tmp->data)))
			msg_exit(EXIT_FAILURE, "cmd", ERR_MALLOC);
		if (data)
		{
			if (!(argv[i++] = ft_strdup(data)))
				return (NULL);
			free(data);
		}
		tmp = tmp->right;
	}
	*argc = i;
	return (argv);
}

void			env_vars_set(t_cmd *cmd)
{
	size_t		i;

	i = 0;
	while (cmd->argv[i])
	{
		env_lst_set(g_envlst, cmd->argv[i], false);
		i++;
	}
	g_exit_code = EXIT_SUCCESS;
}

void			cmd_exec(t_cmd *cmd)
{
	char	*bin;

	bin = cmd->argv[0];
	if (!ft_strncmp(bin, "echo", 10))
		echo_exec(cmd);
	else if (!ft_strncmp(bin, "cd", 10))
		cd_exec(cmd);
	else if (!ft_strncmp(bin, "pwd", 10))
		pwd_exec();
	else if (!ft_strncmp(bin, "export", 10))
		export_exec(cmd);
	else if (!ft_strncmp(bin, "unset", 10))
		unset_exec(cmd);
	else if (!ft_strncmp(bin, "env", 10))
		env_exec(cmd);
	else if (!ft_strncmp(bin, "exit", 10))
	{
		g_exit_code = EXIT_SUCCESS;
		exit(g_exit_code);
	}
	else if (ft_strchr(bin, '='))
		env_vars_set(cmd);
	else
		default_bin_exec(cmd);
}

/*
** EXECUTE CMD:
** 	creates cmd config and run it
*/

void			execute_cmd(t_ast_tree *root_ptr)
{
	t_cmd		cmd;

	if (root_ptr)
	{
		cmd.argc = ast_len(root_ptr);
		if (!(cmd.argv = create_cmd(root_ptr, &cmd.argc)))
			msg_exit(EXIT_FAILURE, root_ptr->data, "Malloc error");
		cmd_exec(&cmd);
		free_argv(&(cmd.argv));
	}
}
