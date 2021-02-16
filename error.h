/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:25:48 by lnovella          #+#    #+#             */
/*   Updated: 2021/02/15 16:41:54 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

# include <errno.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <string.h>

void	msg_exit(int error, char *msg);
void	ft_perror(char *error);
void	check_error(int ret_func, char *error);

#endif
