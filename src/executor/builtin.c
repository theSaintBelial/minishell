/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:04:01 by thesaintbel       #+#    #+#             */
/*   Updated: 2021/03/18 22:23:22 by lnovella         ###   ########.fr       */
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

void			pwd_exec(void)
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
	{
		ft_free(&tmp->value);
		if (!(tmp->value = ft_strdup(value)))
			msg_exit(EXIT_FAILURE, "cd", ERR_MALLOC);
	}
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
