/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:02:55 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/08 15:44:38 by lnovella         ###   ########.fr       */
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

char	**get_path_dirs(t_env *envlst)
{
	char	**path_dirs;
	t_env	*path_node;

	path_dirs = NULL;
	path_node = env_lst_find(envlst, "PATH");
	if (path_node)
		path_dirs = ft_split(path_node->value, ':');
	return (path_dirs);
}

char	*get_binary(char *path_dir, char *bin)
{
	char	*tmp;
	char	*full_bin;

	tmp = NULL;
	full_bin = NULL;
	if (!(tmp = ft_strjoin("/", bin)))
		return (NULL);
	full_bin = ft_strjoin(path_dir, tmp);
	free(tmp);
	return (full_bin);
}

bool	check_for_binary(t_cmd *cmd, int *status)
{
	char	**path_dirs;
	int		i;
	char	*full_bin;
	char	**envp;

	if (!(path_dirs = get_path_dirs(g_envlst)))
		return (false);
	i = 0;
	if (!(envp = env_lst_tostrarr(g_envlst, true)))
		msg_exit(EXIT_FAILURE, "envp", "Malloc error");
	while (path_dirs[i])
	{
		if (!(full_bin = get_binary(path_dirs[i], cmd->argv[0])))
		{
			ft_putendl_fd("malloc error", STDERR_FILENO);
			return (false);
		}
		*status = execve(full_bin, cmd->argv, envp);
		free(full_bin);
		free(path_dirs[i]);
		i++;
	}
	free(path_dirs);
	if ((*status = execve(cmd->argv[0], cmd->argv, envp)) == -1)
	{
		free_argv(&envp);
		return (false);
	}
	free_argv(&envp);
	return (true);
}

int			status_return(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
		if (WTERMSIG(status) == 3)
			return (131);
		if (WTERMSIG(status) == 15)
			return (143);
	}
	return (WEXITSTATUS(status));
}

void	default_bin_exec(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	check_error(pid = fork(), "fork");;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		if (!check_for_binary(cmd, &status))
		{
			// ft_perror("execve", strerror(errno));
			// exit(WEXITSTATUS(status));
			msg_exit(WEXITSTATUS(status), "execve", strerror(errno));
		}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		pid = waitpid(pid, &status, WUNTRACED);
		if ((g_exit_code = status_return(status)) == 130)
			ft_putendl_fd("", STDERR_FILENO);
		if (g_exit_code == 131)
			ft_putendl_fd("Quit:", STDERR_FILENO);
		if (g_exit_code == 143)
			ft_putendl_fd("terminated", STDERR_FILENO);
	}
}

/*
** EXECUTE IO:
** 	1) < file
** 	2) > file
** 	3) >> file
*/
int		execute_io(t_ast_tree *root_ptr, char **in_out, bool *rewrite)
{
	int		fd;
	char	*filename;
	int		flag;

	if (root_ptr && root_ptr->right)
	{
		filename = (root_ptr->right->type == VARIABLE_N ? \
			env_lst_getval(g_envlst, root_ptr->right->data) : \
			root_ptr->right->data);
		if (root_ptr->type == LESS_N)
		{
			fd = open(filename, O_RDONLY);
			in_out[0] = filename;
		}
		else
		{
			*rewrite = (root_ptr->type == GREATER_N ? true : false);
			flag = (*rewrite ? O_TRUNC : O_APPEND);
			fd = open(filename, O_WRONLY | O_CREAT | flag, 0666);
			in_out[1] = filename;
		}
		if (fd == -1)
			return (msg_return(errno, filename, strerror(errno)));
		close(fd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** EXECUTE IO_LIST:
** 		1) IO IO
** 		2) IO IOL
*/
void	execute_iol(t_ast_tree *root_ptr, char **in_out, bool *rewrite)
{
	if (root_ptr)
	{
		if (!execute_io(root_ptr->left, in_out, rewrite))
		{
			if (root_ptr->right && root_ptr->right->type == IO_LIST_N)
				execute_iol(root_ptr->right, in_out, rewrite);
			else
				execute_io(root_ptr->right, in_out, rewrite);
		}
	}
}

/*
** SETS UP STDOUT AND STDIN
** AS PIPE OR REDIRECTS REQUIRE
** 	1) pipes: pipes config
** 	2) in_out: redirects config
** 	3) rewrite: is it required to truncate the file in out redirect
*/
int		redirect_std_in_out(t_dirs *pipes, char **in_out, bool rewrite)
{
	int		fd;
	int		flag;

	if (in_out[0])
	{
		if ((fd = open(in_out[0], O_RDONLY)) == -1)
			return (msg_return(errno, in_out[0], strerror(errno)));
		ft_dup2(fd, STDIN_FILENO);
	}
	else if (pipes->is_in)
		ft_dup2(pipes->in_fd, STDIN_FILENO);
	if (in_out[1])
	{
		flag = (rewrite ? O_TRUNC : O_APPEND);
		if ((fd = open(in_out[1], O_WRONLY | O_CREAT | flag, 0666)) == -1)
			return (msg_return(errno, in_out[0], strerror(errno)));
		ft_dup2(fd, STDOUT_FILENO);
	}
	else if (pipes->is_out)
		ft_dup2(pipes->out_fd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

/*
** EXECUTE CMD_IO:
** 	1) CMD IO
** 	2) CMD IO_LIST
*/
void	execute_cmd_io(t_ast_tree *root_ptr, t_dirs *pipes, char **in_out)
{
	bool	rewrite;

	rewrite = false;
	if (root_ptr->right && root_ptr->right->type == IO_LIST_N)
		execute_iol(root_ptr->right, in_out, &rewrite);
	else
		execute_io(root_ptr->right, in_out, &rewrite);
	if (!g_exit_code)
		if (!redirect_std_in_out(pipes, in_out, rewrite))
			execute_cmd(root_ptr->left);
}

/*
** EXECUTE JOB:
** 	1) CMD
** 	2) CMD_IO
*/
void	execute_job(t_ast_tree *root_ptr, t_dirs *pipes)
{
	char	*in_out[2];
	int		stdout_fd;
	int		stdin_fd;

	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	if (root_ptr)
	{
		in_out[0] = NULL;
		in_out[1] = NULL;
		if (root_ptr->type == CMD_IO_N)
			execute_cmd_io(root_ptr, pipes, in_out);
		else if ((!redirect_std_in_out(pipes, in_out, false)))
			execute_cmd(root_ptr);
	}
	ft_dup2(stdin_fd, STDIN_FILENO);
	ft_dup2(stdout_fd, STDOUT_FILENO);
}

/*
** EXECUTE PIPE:
** 	1) JOB | JOB
** 	2) JOB | PIPE
*/
void	execute_job_pipe(t_ast_tree *root_ptr, t_dirs *pipes)
{
	int			fd[2];
	t_ast_tree	*tmp;

	check_error(pipe(fd), "pipe");
	pipes->is_out = true;
	pipes->out_fd = fd[1];
	execute_job(root_ptr->left, pipes);
	tmp = root_ptr->right;
	while (tmp && tmp->type == PIPE_N)
	{
		close(pipes->out_fd);
		pipes->is_in = true;
		pipes->in_fd = fd[0];
		check_error(pipe(fd), "pipe");
		pipes->is_out = true;
		pipes->out_fd = fd[1];
		execute_job(tmp->left, pipes);
		close(pipes->in_fd);
		tmp = tmp->right;
	}
	close(fd[1]);
	set_dirs_config(pipes);
	pipes->is_in = true;
	pipes->in_fd = fd[0];
	execute_job(tmp, pipes);
	close(fd[0]);
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
