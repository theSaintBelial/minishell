/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:52:17 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 19:52:19 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

extern int	g_exit_code;

void	msg_exit(int error, char *error_place, char *msg)
{
	exit(msg_return(error, error_place, msg));
}

void	ft_perror(char *error_place, char *msg)
{
	ft_putstr_fd(MSH_V": ", STDERR_FILENO);
	ft_putstr_fd(error_place, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	check_error(int ret_func, char *error_place)
{
	if (ret_func == -1)
		msg_exit(errno, error_place, strerror(errno));
}

int		msg_return(int ret, char *error_place, char *msg)
{
	ft_perror(error_place, msg);
	g_exit_code = ret;
	return (ret);
}
