/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:02:55 by lnovella          #+#    #+#             */
/*   Updated: 2021/02/10 20:11:54 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *env_name);

void	set_dirs_config(t_dirs *config)
{
	config->is_in = FALSE;
	config->is_out = FALSE;
	config->in_fd = 0;
	config->out_fd = 0;
}

void	echo_exec(t_cmd *cmd)
{
	char	*str;
	int		i;
	int		func_n;
	void	(*funcs[2])(char *, int);

	funcs[0] = ft_putstr_fd;
	funcs[1] = ft_putendl_fd;
	i = 1;
	func_n = 1;
	if (cmd->argc > 1 && !ft_strncmp(cmd->argv[i], "-n", 2))
		func_n = 0;
	!func_n ? i++ : 0;
	while (cmd->argv[i])
	{
		str = (cmd->argv[i] ? cmd->argv[i] : "");
		ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		i++;
		if (cmd->argv[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	(*funcs[func_n])("", STDOUT_FILENO);
}

void	pwd_exec(t_cmd *cmd)
{
	char	*dir;
	pid_t	pid;

	if ((dir = getcwd(NULL, 0)))
	{
		ft_putendl_fd(dir, STDOUT_FILENO);
		free(dir);
	}
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

char	*get_current_home_path()
{
	char	*current_home_path;
	int		i;

	i = 0;
	while (g_envp[i])
	{
		if (!ft_strncmp(g_envp[i], "HOME=", 5))
			return (g_envp[i] + 5);
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
		current_home_path = get_current_home_path();
		if (chdir(current_home_path))
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
	{
		if (chdir(cmd->argv[1]))
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
}

void	export_exec(){}
void	unset_exec(){}

void	env_exec(t_cmd *cmd)
{
	t_env	*tmp;

	if (cmd->argc > 1)
	{
		ft_putendl_fd("env: Too many args", STDERR_FILENO);
		g_exit_code = 1;
		return ;
	}
	tmp = g_envlst;
	while (tmp)
	{
		ft_putstr_fd(tmp->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(tmp->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
}

char	**handle_path_dirs()
{
	int		i;
	char	**path_dirs;

	i = 0;
	while (g_envp[i])
	{
		if (!ft_strncmp(g_envp[i], "PATH=", 5))
		{
			if (!(path_dirs = ft_split(g_envp[i] + 5, ':')))
				ft_putendl_fd("Malloc error", STDERR_FILENO);
			return (path_dirs);
		}
		i++;
	}
	return (NULL);
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

	if (!(path_dirs = handle_path_dirs()))
		return (FALSE);
	i = 0;
	while (path_dirs[i])
	{
		if (!(full_bin = get_binary(path_dirs[i], cmd->argv[0])))
		{
			ft_putendl_fd("malloc error", STDERR_FILENO);
			return (FALSE);
		}
		*status = execve(full_bin, cmd->argv, g_envp);
		free(full_bin);
		free(path_dirs[i]);
		i++;
	}
	free(path_dirs);
	if ((*status = execve(cmd->argv[0], cmd->argv, g_envp)) == -1)
		return (FALSE);
	return (TRUE);
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

	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		if (!check_for_binary(cmd, &status))
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(WEXITSTATUS(status));
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

void	cmd_exec(t_cmd *cmd)
{
	char	*bin;

	bin = cmd->argv[0];
	if (!ft_strncmp(bin, "echo", 10))
		echo_exec(cmd);
	else if (!ft_strncmp(bin, "cd", 10))
		cd_exec(cmd);
	else if (!ft_strncmp(bin, "pwd", 10))
		pwd_exec(cmd);
	else if (!ft_strncmp(bin, "export", 10))
		export_exec();
	else if (!ft_strncmp(bin, "unset", 10))
		unset_exec();
	else if (!ft_strncmp(bin, "env", 10))
		env_exec(cmd);
	else if (!ft_strncmp(bin, "exit", 10))
	{
		exit(EXIT_SUCCESS);
	}
	else
		default_bin_exec(cmd);
}

void	free_argv(char ***argv)
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

int		cmd_argv_size(t_ast_tree *root_ptr)
{
	t_ast_tree	*tmp;
	int			i;

	i = 0;
	if (root_ptr)
	{
		tmp = root_ptr;
		while (tmp)
		{
			i++;
			tmp = tmp->right;
		}
	}
	return (i);
}

char	**create_cmd(t_ast_tree *root_ptr, int size)
{
	t_ast_tree	*tmp;
	char		**argv;
	int			i;
	char		*data;

	argv = NULL;
	if (root_ptr)
	{
		if (!(argv = (char **)ft_calloc(size + 1, sizeof(char *))))
		{
			ft_putendl_fd("Memory allocation error", STDERR_FILENO);
			return (NULL);
		}
		tmp = root_ptr;
		i = 0;
		while (tmp)
		{
			data = (tmp->type == VARIABLE_N ? get_env_value(tmp->data) : tmp->data);
			if (data)
			{
				if (!(argv[i++] = ft_strdup(data)))
				{
					ft_putendl_fd("Memory allocation error", STDERR_FILENO);
					free_argv(&argv);
					return (NULL);
				}
				tmp = tmp->right;
			}
		}
	}
	return (argv);
}

void	execute_config(t_ast_tree *root_ptr)
{
	t_ast_tree	*tmp;
	int			size;
	t_cmd		cmd;

	if (root_ptr)
	{
		size = cmd_argv_size(root_ptr);
		if (!(cmd.argv = create_cmd(root_ptr, size)))
		{
			ft_putendl_fd("Memory allocation error", STDERR_FILENO);
			return ;
		}
		cmd.argc = size;
		cmd_exec(&cmd);
		free_argv(&(cmd.argv));
	}
}

char	*get_env_value(char *env_name)
{
	t_env	*cur;
	char	*env_value;

	env_value = NULL;
	cur = ft_env_find(g_envlst, env_name);
	if (cur)
		env_value = cur->value;
	else if (ft_strncmp(env_name, "?", 1000) == 0)
		env_value = ft_itoa(g_exit_code);
	return (env_value);
}

/*
** EXECUTE LINE:
** 		1) config < file
** 		2) config > file
** 		3) config >> file
**		4) config
*/
void	execute_io(t_ast_tree *root_ptr, char **in_out, bool *rewrite)
{
	int		fd;
	char	*filename;

	filename = NULL;
	if (root_ptr && root_ptr->right)
	{
		filename = (root_ptr->right->type == VARIABLE_N ? get_env_value(root_ptr->right->data) : root_ptr->data);
		if (!filename)
		{
			ft_putendl_fd("wtf u doin??? redirect error", STDERR_FILENO);
			g_exit_code = 1;
			return ;
		}
		if (root_ptr->type == LESS_N)
		{
			fd = open(filename, O_RDONLY);
			in_out[0] = filename;
		}
		else if (root_ptr->type == GREATER_N)
		{
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			in_out[1] = filename;
			*rewrite = TRUE;
		}
		else if (root_ptr->type == D_GREATER_N)
		{
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
			in_out[1] = filename;
			*rewrite = FALSE;
		}
		if (fd == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			g_exit_code = 1;
			return ;
		}
		close(fd);
	}
}

void	execute_iol(t_ast_tree *root_ptr, char **in_out, bool *rewrite)
{
	if (root_ptr)
	{
		execute_io(root_ptr->left, in_out, rewrite);
		if (!g_exit_code)
		{
			if (root_ptr->right && root_ptr->right->type == IO_LIST_N)
				execute_iol(root_ptr->right, in_out, rewrite);
			else
				execute_io(root_ptr->right, in_out, rewrite);
		}
	}
}

void	redirect_std_in_out(t_dirs *pipes, char **in_out, bool rewrite)
{
	int		fd;

	if (in_out[0])
	{
		if ((fd = open(in_out[0], O_RDONLY)) == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (pipes->is_in)
		dup2(pipes->in_fd, STDIN_FILENO);
	if (in_out[1])
	{
		if (rewrite)
			fd = open(in_out[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			fd = open(in_out[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return ;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (pipes->is_out)
		dup2(pipes->out_fd, STDOUT_FILENO);
}

void	execute_cmd_io(t_ast_tree *root_ptr, t_dirs *pipes, char **in_out)
{
	bool	rewrite;

	rewrite = FALSE;
	if (root_ptr->right && root_ptr->right->type == IO_LIST_N)
		execute_iol(root_ptr->right, in_out, &rewrite);
	else
		execute_io(root_ptr->right, in_out, &rewrite);
	if (!g_exit_code)
	{
		redirect_std_in_out(pipes, in_out, rewrite);
		execute_config(root_ptr->left);
	}
}

void	execute_job(t_ast_tree *root_ptr, t_dirs *pipes)
{
	char	*in_out[2];
	int stdout_fd;
	int stdin_fd;

	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	if (root_ptr)
	{
		in_out[0] = NULL;
		in_out[1] = NULL;
		if (root_ptr->type == CMD_IO_N)
			execute_cmd_io(root_ptr, pipes, in_out);
		else
		{
			redirect_std_in_out(pipes, in_out, FALSE);
			execute_config(root_ptr);
		}
	}
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
}

void	execute_job_pipe(t_ast_tree *root_ptr, t_dirs *pipes)
{
	int			fd[2];
	t_ast_tree	*tmp;

	if (pipe(fd) == -1)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	pipes->is_out = TRUE;
	pipes->out_fd = fd[1];
	execute_job(root_ptr->left, pipes);
	tmp = root_ptr->right;
	while (tmp && tmp->type == PIPE_N)
	{
		close(pipes->out_fd);
		pipes->is_in = TRUE;
		pipes->in_fd = fd[0];
		if (pipe(fd) == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return ;
		}
		pipes->is_out = TRUE;
		pipes->out_fd = fd[1];
		execute_job(tmp->left, pipes);
		close(pipes->in_fd);
		tmp = tmp->right;
	}
	close(fd[1]);
	set_dirs_config(pipes);
	pipes->is_in = TRUE;
	pipes->in_fd = fd[0];
	execute_job(tmp, pipes);
	close(fd[0]);
}

/*
** EXECUTE COMMAND:
** 		1) JOB | COMMAND
** 		2) JOB
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
void	executor(t_ast_tree *root_ptr)
{
	execute_line(root_ptr);
}
