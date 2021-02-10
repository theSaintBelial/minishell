/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_vars.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:02:23 by lnovella          #+#    #+#             */
/*   Updated: 2021/02/10 19:15:31 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

# include "minishell.h"

char        **g_envp;
int         g_exit_code;
t_ast_tree  *g_root;
t_env       *g_envlst;

#endif
