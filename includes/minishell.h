/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:16 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/19 13:16:07 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <signal.h>

# include <stdbool.h>

# define PROMPT "\033[1;35mour-minishell$>\033[0m"

# define MSH_V "shell_v1.0"

typedef struct		s_vars
{
	char			*line;
	int				status;
	int				count;
	int				gnl_check;
	int				loop;
	int				checker;
}					t_vars;

/*
** file: executor.c
** running all the process
** root_ptr - ptr to the root of the tree
*/

#endif
