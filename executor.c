/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:02:55 by lnovella          #+#    #+#             */
/*   Updated: 2021/01/23 11:44:55 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp;

void	task_config(t_task *task)
{
	task->is_pipe_in = FALSE;
	task->is_pipe_out = FALSE;
	task->pipe_in_fd = 0;
	task->pipe_out_fd = 0;
}

void	print_cmd_config(t_cmd *cmd)
{
	printf("CMD CONFIG:\n");
	if (cmd->argv)
	{
		printf("ARGV:\n");
		for (int i = 0; cmd->argv[i]; i++)
			printf("\t[%d]: %s\n", i, cmd->argv[i]);
	}
	if (cmd->config)
	{
		printf("TASK CONFIG:\n");
		printf("\tis_pipe_in: %s\n", cmd->config->is_pipe_in ? "true" : "false");
		printf("\tis_pipe_out: %s\n", cmd->config->is_pipe_out ? "true" : "false");
		printf("\tfd_pipe_in: %d\n", cmd->config->pipe_in_fd);
		printf("\tfd_pipe_out: %d\n", cmd->config->pipe_out_fd);
	}
	if (cmd->in_out)
	{
		printf("IN_OUT:\n");
		printf("\t[IN]: %s\n", cmd->in_out[0]);
		printf("\t[OUT]: %s\n", cmd->in_out[1]);
	}
	printf("REWRITE: %s\n\n------------------------------------\n", cmd->rewrite ? "true" : "false");
}

void	echo_exec(){}
void	cd_exec(){}
void	pwd_exec(){}
void	export_exec(){}
void	unset_exec(){}
void	env_exec(){}
void	exit_exec(){}

void	default_bin_exec(t_cmd *cmd)
{
	pid_t	pid;
	int		stdout_fd;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// child process
		stdout_fd = dup(STDOUT_FILENO); // buf the stdout

		if (cmd->in_out[0])
			;
		else if (cmd->in_out[1])
			;

		if (cmd->config->is_pipe_in)
			;
		else if (cmd->config->is_pipe_out)
			;

		for (int i = 0; envp[i]; i++)
			printf("[%d]: %s\n", i, envp[i]);

		if (execve(cmd->argv[0], cmd->argv, envp) == -1)
		{
			dup2(stdout_fd, STDOUT_FILENO);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		// parent - waiting while child ends
		while (waitpid(pid, NULL, 0) <= 0)
			;
	}
}

void	cmd_exec(t_cmd *cmd)
{
	// print_cmd_config(cmd);

	char	*bin;

	bin = cmd->argv[0];
	if (!ft_strncmp(bin, "echo", 10))
		echo_exec();
	else if (!ft_strncmp(bin, "cd", 10))
		cd_exec();
	else if (!ft_strncmp(bin, "pwd", 10))
		pwd_exec();
	else if (!ft_strncmp(bin, "export", 10))
		export_exec();
	else if (!ft_strncmp(bin, "unset", 10))
		unset_exec();
	else if (!ft_strncmp(bin, "env", 10))
		env_exec();
	else if (!ft_strncmp(bin, "exit", 10))
		exit(EXIT_SUCCESS);
	else
		default_bin_exec(cmd);
}

void	execute_task(t_ast_tree *root_ptr, t_task *config, char *in_out[2], bool rewrite)
{
	t_ast_tree	*tmp;
	int			i;
	t_cmd		cmd;

	if (root_ptr)
	{
		tmp = root_ptr;
		while (tmp)
		{
			i++;
			tmp = tmp->right;
		}
		cmd.argv = (char **)ft_calloc(i + 1, sizeof(char *));
		tmp = root_ptr;
		i = 0;
		while (tmp)
		{
			cmd.argv[i++] = ft_strdup(tmp->data);
			tmp = tmp->right;
		}
		cmd.argc = i;
		cmd.config = config;
		cmd.in_out = in_out;
		cmd.rewrite = rewrite;
		cmd_exec(&cmd);
	}
}

/*
** EXECUTE JOB:
** 		1) TASK < file
** 		2) TASK > file
** 		3) TASK >> file
**		4) TASK
*/

void	execute_job(t_ast_tree *root_ptr, t_task *config)
{
	char	*in_out[2];

	in_out[0] = NULL;
	in_out[1] = NULL;
	if (root_ptr->type == LESS_N)
	{
		in_out[0] = root_ptr->right->data;
		execute_task(root_ptr->left, config, in_out, FALSE);
	}
	else if (root_ptr->type == GREATER_N)
	{
		in_out[1] = root_ptr->right->data;
		execute_task(root_ptr->left, config, in_out, FALSE);
	}
	else if (root_ptr->type == D_GREATER_N)
	{
		in_out[1] = root_ptr->right->data;
		execute_task(root_ptr->left, config, in_out, TRUE);
	}
	else
		execute_task(root_ptr, config, in_out, FALSE);
}

void	execute_job_pipe(t_ast_tree *root_ptr)
{
	printf("Im here - pipe is alive!!!\n");
}

/*
** EXECUTE COMMAND:
** 		1) JOB | COMMAND
** 		2) JOB
*/

void	execute_command(t_ast_tree *root_ptr)
{
	t_task	config;

	task_config(&config);
	if (root_ptr)
	{
		if (root_ptr->type == PIPE_N)
			execute_job_pipe(root_ptr);
		else
			execute_job(root_ptr, &config);
	}
}

/*
** EXECUTE LINE:
** 		1) COMMAND ; (LINE)?
** 		2) COMMAND
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

void	executor(t_ast_tree *root_ptr, char **envp_buf)
{
	envp = envp_buf;
	execute_line(root_ptr);
}
