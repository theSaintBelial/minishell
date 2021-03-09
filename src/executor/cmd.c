/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thesaintbelial <thesaintbelial@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:17:07 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/07 12:02:52 by thesaintbel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "parser.h"
#include "env_lst.h"
#include <ft_string.h>
#include <ft_stdlib.h>
#include "builtin.h"

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

	argv = NULL;
	if (root_ptr)
	{
		if (!(argv = (char **)ft_calloc(*argc + 1, sizeof(char *))))
			return (NULL);
		tmp = root_ptr;
		i = 0;
		while (tmp)
		{
			if ((data = (tmp->type == VARIABLE_N ? \
					env_lst_getval(g_envlst, tmp->data) : tmp->data)))
			{
				if (!(argv[i++] = ft_strdup(data)))
				{
					free_argv(&argv);
					return (NULL);
				}
			}
			tmp = tmp->right;
		}
		*argc = i;
	}
	return (argv);
}

void	cmd_exec(t_cmd *cmd)
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
	{
		for (int i = 0; cmd->argv[i]; i++)
			env_lst_set(g_envlst, cmd->argv[i], false);
	}
	else
		default_bin_exec(cmd);
}

/*
** EXECUTE CMD:
** 	creates cmd config and run it
*/
void	execute_cmd(t_ast_tree *root_ptr)
{
	t_ast_tree	*tmp;
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
