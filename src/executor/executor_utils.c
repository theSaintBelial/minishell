/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:37:44 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 22:01:50 by lnovella         ###   ########.fr       */
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

extern t_env	*g_envlst;

char			*get_filename(t_ast_tree *node)
{
	char	*filename;

	if (node->type == VARIABLE_N)
		filename = env_lst_getval(g_envlst, node->data);
	else if (!(filename = ft_strdup(node->data)))
		msg_exit(EXIT_FAILURE, "IO", ERR_MALLOC);
	return (filename);
}

/*
** EXECUTE IO:
** 	1) < file
** 	2) > file
** 	3) >> file
*/

int				execute_io(t_ast_tree *root_ptr, char **in_out, bool *rewrite)
{
	int		fd;
	char	*filename;
	int		flag;

	if (!(root_ptr && root_ptr->right
	&& (filename = get_filename(root_ptr->right))))
		return (msg_return(EXIT_FAILURE, root_ptr->right->data, "Bad redir"));
	if (root_ptr->type == LESS_N)
	{
		fd = open(filename, O_RDONLY);
		ft_free(in_out + 0);
		in_out[0] = filename;
	}
	else
	{
		*rewrite = (root_ptr->type == GREATER_N ? true : false);
		flag = (*rewrite ? O_TRUNC : O_APPEND);
		fd = open(filename, O_WRONLY | O_CREAT | flag, 0666);
		ft_free(in_out + 1);
		in_out[1] = filename;
	}
	if (fd == -1)
		return (msg_return(errno, root_ptr->right->data, strerror(errno)));
	return (close(fd));
}

/*
** EXECUTE IO_LIST:
** 		1) IO IO
** 		2) IO IOL
*/

bool			execute_iol(t_ast_tree *root_ptr, char **in_out, bool *rewrite)
{
	bool	ret;

	ret = EXIT_SUCCESS;
	if (root_ptr)
	{
		if (!(ret = execute_io(root_ptr->left, in_out, rewrite)))
		{
			if (root_ptr->right && root_ptr->right->type == IO_LIST_N)
				ret = execute_iol(root_ptr->right, in_out, rewrite);
			else
				ret = execute_io(root_ptr->right, in_out, rewrite);
		}
	}
	return (ret);
}
