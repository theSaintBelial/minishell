/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thesaintbelial <thesaintbelial@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:04:04 by thesaintbel       #+#    #+#             */
/*   Updated: 2021/03/07 12:02:37 by thesaintbel      ###   ########.fr       */
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
