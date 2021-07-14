/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:12:53 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 22:38:37 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "cmd.h"

typedef struct		s_dirs
{
	bool		is_in;
	bool		is_out;
	int			in_fd;
	int			out_fd;
}					t_dirs;

void				executor(t_ast_tree *root_ptr);
void				default_bin_exec(t_cmd *cmd);
bool				execute_iol(t_ast_tree *root_ptr, \
						char **in_out, bool *rewrite);
int					execute_io(t_ast_tree *root_ptr, \
						char **in_out, bool *rewrite);
void				execute_job_pipe(t_ast_tree *root_ptr, t_dirs *pipes);
void				execute_job(t_ast_tree *root_ptr, t_dirs *pipes);
void				execute_cmd_io(t_ast_tree *root_ptr, \
									t_dirs *pipes, char **in_out);
void				ft_dup2(int old_fd, int new_fd);
void				set_dirs_config(t_dirs *config);
void				handle_signals(void);
void				default_signals(void);

#endif
