/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:31:36 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 22:31:56 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_lst.h"
#include "errors.h"
#include "cmd.h"
#include "executor.h"
#include <ft_string.h>

extern int		g_exit_code;
extern t_env	*g_envlst;

char			**get_path_dirs(t_env *envlst)
{
	char	**path_dirs;
	t_env	*path_node;

	path_dirs = NULL;
	if (!(path_node = env_lst_find(envlst, "PATH")))
		return (NULL);
	if (!(path_dirs = ft_split(path_node->value, ':')))
		msg_exit(EXIT_FAILURE, "execve", ERR_MALLOC);
	return (path_dirs);
}

char			*get_binary(char *path_dir, char *bin)
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

bool			check_for_binary(t_cmd *cmd, int *status)
{
	char	**path_dirs;
	int		i;
	char	*full_bin;
	char	**envp;

	if (!(envp = env_lst_tostrarr(g_envlst, true)))
		msg_exit(EXIT_FAILURE, "envp", "Malloc error");
	if ((path_dirs = get_path_dirs(g_envlst)))
	{
		i = 0;
		while (path_dirs[i])
		{
			if (!(full_bin = get_binary(path_dirs[i], cmd->argv[0])))
				msg_exit(EXIT_FAILURE, "execve", ERR_MALLOC);
			*status = execve(full_bin, cmd->argv, envp);
			free(full_bin);
			free(path_dirs[i]);
			i++;
		}
		free(path_dirs);
	}
	*status = execve(cmd->argv[0], cmd->argv, envp);
	free_argv(&envp);
	return (*status == -1 ? false : true);
}

int				status_return(int status)
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

void			default_bin_exec(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	check_error(pid = fork(), "fork");
	if (pid == 0)
	{
		default_signals();
		if (!check_for_binary(cmd, &status))
			msg_exit(WEXITSTATUS(status), "execve", strerror(errno));
	}
	else
	{
		handle_signals();
		pid = waitpid(pid, &status, WUNTRACED);
		if ((g_exit_code = status_return(status)) == 130)
			ft_putendl_fd("", STDERR_FILENO);
		if (g_exit_code == 131)
			ft_putendl_fd("Quit:", STDERR_FILENO);
		if (g_exit_code == 143)
			ft_putendl_fd("terminated", STDERR_FILENO);
	}
}
