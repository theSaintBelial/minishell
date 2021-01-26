/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:02:55 by lnovella          #+#    #+#             */
/*   Updated: 2021/01/26 23:23:51 by lnovella         ###   ########.fr       */
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

void	pwd_exec(t_cmd *cmd)
{
	char	*dir;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		; // error
	else if (pid == 0)
	{
		if (cmd->in_out[1])
			;
		else if (cmd->config->is_pipe_out)
			;

		if ((dir = getcwd(NULL, 0)))
		{
			ft_putendl_fd(dir, STDOUT_FILENO);
			free(dir);
		}
		else
			;
		exit(EXIT_SUCCESS);
	}
	else
		while (waitpid(pid, NULL, 0) <= 0)
			;

}

char	*get_current_home_path()
{
	char	*current_home_path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
		{
			current_home_path = ft_strchr(envp[i], '=') + 1;
			return (current_home_path);
		}
		i++;
	}
	return (NULL);
}

void	cd_exec(t_cmd *cmd)
{
	char	*current_home_path;

	if (cmd->argc > 2)
		ft_putendl_fd("cd: Too many arguments", 2);
	else if (cmd->argc == 1)
	{
		// get to home
		current_home_path = get_current_home_path();
		if (chdir(current_home_path))
			// error
			;
	}
	else
	{
		if (chdir(cmd->argv[1]))
			// error
			;
	}
}

void	export_exec(){}
void	unset_exec(){}
void	env_exec()
{

}

char	**handle_path_dirs()
{
	int		i;
	char	**path_dirs;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			if (!(path_dirs = ft_split(ft_strchr(envp[i], '=') + 1, ':')))
			{
				; // error
				exit(EXIT_FAILURE);
			}
			return (path_dirs);
		}
		i++;
	}
	return (NULL);
}

bool	check_for_binary(t_cmd *cmd)
{
	char	**path_dirs;
	int		i;
	char	*full_bin;
	char	*bin;

	if (!(path_dirs = handle_path_dirs()))
	{
		// error
		return (FALSE);
	}
	i = 0;
	while (path_dirs[i])
	{
		if (!(bin = ft_strjoin("/", cmd->argv[0])))
		{
			; // error
			// free(path_dirs)
			exit(EXIT_FAILURE);
		}
		if (!(full_bin = ft_strjoin(path_dirs[i], bin)))
		{
			; // error
			// free path_dirs
			return (FALSE);
		}
		if (execve(full_bin, cmd->argv, envp) != -1)
		{
			// free all
			return (TRUE);
		}
		i++;
	}
	if (execve(cmd->argv[0], cmd->argv, envp) == -1)
	{
		; // error
		return (FALSE);
	}
	return (TRUE);
}

void	default_bin_exec(t_cmd *cmd)
{
	pid_t	pid;
	int		stdout_fd;
	int		fd;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		stdout_fd = dup(STDOUT_FILENO);
		if (cmd->in_out[0])
		{
			if ((fd = open(cmd->in_out[0], O_RDONLY)) == -1)
				// error;
				exit(EXIT_FAILURE);
			dup2(fd, STDIN_FILENO);
		}
		else if (cmd->config->is_pipe_in)
			dup2(cmd->config->pipe_in_fd, STDIN_FILENO);
		if (cmd->in_out[1])
		{
			if (cmd->rewrite)
				fd = open(cmd->in_out[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else
				fd = open(cmd->in_out[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd == -1)
				// error;
				exit(EXIT_FAILURE);
			dup2(fd, STDOUT_FILENO);
		}
		else if (cmd->config->is_pipe_out)
			dup2(cmd->config->pipe_out_fd, STDOUT_FILENO);
		if (!check_for_binary(cmd))
		{
			dup2(stdout_fd, STDOUT_FILENO);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		while (waitpid(pid, NULL, 0) <= 0)
			;
}

void	cmd_exec(t_cmd *cmd)
{
	char	*bin;

	bin = cmd->argv[0];
	if (!ft_strncmp(bin, "echo", 10))
		echo_exec();
	else if (!ft_strncmp(bin, "cd", 10))
		cd_exec(cmd);
	else if (!ft_strncmp(bin, "pwd", 10))
		pwd_exec(cmd);
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
		i = 0;
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
		execute_task(root_ptr->left, config, in_out, TRUE);
	}
	else if (root_ptr->type == D_GREATER_N)
	{
		in_out[1] = root_ptr->right->data;
		execute_task(root_ptr->left, config, in_out, FALSE);
	}
	else
		execute_task(root_ptr, config, in_out, FALSE);
}

void	execute_job_pipe(t_ast_tree *root_ptr, t_task *config)
{
	int			fd[2];
	t_ast_tree	*tmp;

	pipe(fd);
	config->is_pipe_out = TRUE;
	config->pipe_out_fd = fd[1];
	execute_job(root_ptr->left, config);

	// TODO: multi pipes handle (use while)
	tmp = root_ptr->right;
	while (tmp && tmp->type == PIPE_N)
	{
		close(config->pipe_out_fd);
		config->is_pipe_in = TRUE;
		config->pipe_in_fd = fd[0];

		pipe(fd);
		config->is_pipe_out = TRUE;
		config->pipe_out_fd = fd[1];
		execute_job(tmp->left, config);
		close(config->pipe_in_fd);
		tmp = tmp->right;
	}
	close(fd[1]);
	task_config(config);
	config->is_pipe_in = TRUE;
	config->pipe_in_fd = fd[0];
	execute_job(tmp, config);
	close(fd[0]);
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
			execute_job_pipe(root_ptr, &config);
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
