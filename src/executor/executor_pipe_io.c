/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_io.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:36:40 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 22:09:51 by lnovella         ###   ########.fr       */
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
	bool	ret;

	ret = EXIT_SUCCESS;
	rewrite = false;
	if (root_ptr->right && root_ptr->right->type == IO_LIST_N)
		ret = execute_iol(root_ptr->right, in_out, &rewrite);
	else
		ret = execute_io(root_ptr->right, in_out, &rewrite);
	if (!ret)
		if (!redirect_std_in_out(pipes, in_out, rewrite))
			execute_cmd(root_ptr->left);
	ft_free(in_out + 0);
	ft_free(in_out + 1);
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

int		set_pipe(int fd, bool *is)
{
	*is = true;
	return (fd);
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
	pipes->out_fd = set_pipe(fd[1], &(pipes->is_out));
	execute_job(root_ptr->left, pipes);
	tmp = root_ptr->right;
	while (tmp && tmp->type == PIPE_N)
	{
		close(pipes->out_fd);
		pipes->in_fd = set_pipe(fd[0], &(pipes->is_in));
		check_error(pipe(fd), "pipe");
		pipes->out_fd = set_pipe(fd[1], &(pipes->is_out));
		execute_job(tmp->left, pipes);
		close(pipes->in_fd);
		tmp = tmp->right;
	}
	close(fd[1]);
	set_dirs_config(pipes);
	pipes->in_fd = set_pipe(fd[0], &(pipes->is_in));
	execute_job(tmp, pipes);
	close(fd[0]);
}
