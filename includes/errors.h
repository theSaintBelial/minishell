/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:25:48 by lnovella          #+#    #+#             */
/*   Updated: 2021/02/19 13:09:03 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
#define ERRORS_H

# include <errno.h>
# include <string.h>
# include <ft_stdio.h>
# include <unistd.h>

void	msg_exit(int error, char *msg);
void	ft_perror(char *error);
void	check_error(int ret_func, char *error);

#endif
