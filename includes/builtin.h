/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:33:32 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 19:33:34 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "cmd.h"

void	env_exec(t_cmd *cmd);
void	unset_exec(t_cmd *cmd);
void	export_exec(t_cmd *cmd);
int		cd_exec(t_cmd *cmd);
void	pwd_exec();
void	echo_exec(t_cmd *cmd);

#endif
