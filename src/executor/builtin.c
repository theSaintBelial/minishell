/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thesaintbelial <thesaintbelial@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:04:01 by thesaintbel       #+#    #+#             */
/*   Updated: 2021/03/07 10:06:01 by thesaintbel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <ft_string.h>
#include <ft_stdio.h>
#include "env_lst.h"
#include "errors.h"

extern t_env	*g_envlst;
extern int		g_exit_code;

void			echo_exec(t_cmd *cmd)
{
	int		i;
	char	*str;
	int		func_n;
	void	(*funcs[2])(char *, int);

	funcs[0] = ft_putstr_fd;
	funcs[1] = ft_putendl_fd;
	i = 1;
	str = NULL;
	func_n = 1;
	if (cmd->argc > 1 && !ft_strncmp(cmd->argv[i], "-n", 2))
		func_n = 0;
	!func_n ? i++ : 0;
	while (cmd->argv[i])
	{
		str = (cmd->argv[i] ? cmd->argv[i] : "");
		ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		if (cmd->argv[++i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	(*funcs[func_n])("", STDOUT_FILENO);
	g_exit_code = EXIT_SUCCESS;
}

void			pwd_exec()
{
	char	*dir;

	if ((dir = getcwd(NULL, 0)))
	{
		ft_putendl_fd(dir, STDOUT_FILENO);
		free(dir);
		g_exit_code = EXIT_SUCCESS;
	}
	else
		msg_return(errno, "pwd", strerror(errno));
}

bool			env_lst_update_value(t_env *envlst, char *name, char *value)
{
	t_env	*tmp;

	if (!name || !value)
		return (false);
	if ((tmp = env_lst_find(envlst, name)))
		tmp->value = ft_strdup(value);
	else
	{
		if (!(tmp = env_lst_new(ft_strdup(name), ft_strdup(value), true)))
			msg_exit(EXIT_FAILURE, "cd", ERR_MALLOC);
		env_lst_add_back(&envlst, tmp);
	}
	return (true);
}

int				cd2path_exec(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;
	t_env	*tmp;

	if (!(oldpwd = getcwd(NULL, 0)))
		return (msg_return(errno, "getcwd", strerror(errno)));
	if (chdir(cmd->argv[1]))
	{
		free(oldpwd);
		return (msg_return(errno, "chdir", strerror(errno)));
	}
	if (!(pwd = getcwd(NULL, 0)))
		return (msg_return(errno, "getcwd", strerror(errno)));
	env_lst_update_value(g_envlst, "PWD", pwd);
	env_lst_update_value(g_envlst, "OLDPWD", oldpwd);
	free(pwd);
	free(oldpwd);
	return (EXIT_SUCCESS);
}

int				cd_exec(t_cmd *cmd)
{
	char	*home_path;
	t_env	*tmp;
	char	*oldpwd;
	char	*pwd;

	if (cmd->argc > 2)
		return (msg_return(EXIT_FAILURE, "cd", "Too many arguments"));
	else if (cmd->argc == 1)
	{
		if (!(home_path = env_lst_getval(g_envlst, "HOME")))
			return (msg_return(EXIT_FAILURE, "cd", "HOME not set"));
		if (chdir(home_path))
			msg_return(errno, "cd", strerror(errno));
		free(home_path);
	}
	else
		return (g_exit_code = cd2path_exec(cmd));
	return ((g_exit_code = EXIT_SUCCESS));
}

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
	t_env	*tmp;

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

