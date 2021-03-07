/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thesaintbelial <thesaintbelial@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:16:47 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/05 12:25:31 by thesaintbel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H

# define CMD_H

# include "ast.h"
# include "builtin.h"

typedef struct	s_cmd
{
	char		**argv;
	int			argc;
}				t_cmd;

void			free_argv(char ***argv);
char			**create_cmd(t_ast_tree *root_ptr, int *argc);
void			execute_cmd(t_ast_tree *root_ptr);
void			cmd_exec(t_cmd *cmd);

#endif
