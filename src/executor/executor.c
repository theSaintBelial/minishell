/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:02:55 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 20:37:33 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdio.h>
#include <ft_string.h>
#include <ft_stdlib.h>
#include "parser.h"
#include "env_lst.h"
#include "executor.h"
#include "errors.h"
#include "cmd.h"
#include "builtin.h"

int				g_exit_code;
extern t_env	*g_envlst;

void	ft_dup2(int old_fd, int new_fd)
{
	check_error(dup2(old_fd, new_fd), "dup2");
	check_error(close(old_fd), "close");
}

void	set_dirs_config(t_dirs *config)
{
	config->is_in = false;
	config->is_out = false;
	config->in_fd = 0;
	config->out_fd = 0;
}

/*
** EXECUTE COMMAND:
** 	1) JOB | COMMAND
** 	2) JOB
*/

void	execute_command(t_ast_tree *root_ptr)
{
	t_dirs	pipes;

	set_dirs_config(&pipes);
	if (root_ptr)
	{
		if (root_ptr->type == PIPE_N)
			execute_job_pipe(root_ptr, &pipes);
		else
			execute_job(root_ptr, &pipes);
	}
}

/*
** EXECUTE LINE:
** 	1) COMMAND ; (LINE)?
** 	2) COMMAND
*/

void	execute_line(t_ast_tree *root_ptr)
{
	if (root_ptr)
	{
		if (root_ptr->type == SEMICOLON_N)
		{
			execute_command(root_ptr->left);
			execute_line(root_ptr->right);
		}
		else
			execute_command(root_ptr);
	}
}

/*
** EXECUTE ASTREE
*/

void	executor(t_ast_tree *root_ptr)
{
	execute_line(root_ptr);
	free_tree(&root_ptr);
}
