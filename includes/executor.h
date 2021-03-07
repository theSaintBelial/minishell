/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:12:53 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/01 14:18:39 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"

typedef struct	s_dirs
{
	bool		is_in;
	bool		is_out;
	int			in_fd;
	int			out_fd;
}				t_dirs;

void				executor(t_ast_tree *root_ptr);

#endif
