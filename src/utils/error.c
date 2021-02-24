/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:41:30 by lnovella          #+#    #+#             */
/*   Updated: 2021/02/24 17:21:51 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

extern int	g_exit_code;

void	msg_exit(int error, char *msg)
{
	ft_putstr_fd("error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_exit_code = error;
	exit(error);
}

void	ft_perror(char *error)
{
	if (error)
	{
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	check_error(int ret_func, char *error)
{
	if (ret_func == -1)
	{
		ft_perror(error);
		exit(errno);
	}
}

int		putstr_err(char *msg, int ret)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (ret);
}
