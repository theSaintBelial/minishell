/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:25:48 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/02 11:50:25 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>
# include <string.h>
# include <ft_stdio.h>
# include <unistd.h>

# define MSH_V "shell_v1.0"
# define ERR_MALLOC "Malloc error"

void	msg_exit(int error, char *error_place, char *msg);
void	ft_perror(char *error_place, char *msg);
void	check_error(int ret_func, char *error_place);
int		msg_return(int ret, char *error_place, char *msg);

#endif
