/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:31:18 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 19:31:20 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# define C_NULL 0

# include "minishell.h"

/*
** TOKEN DEFINITION
*/
typedef struct		s_token
{
	char			*data;
	char			type;
	struct s_token	*next;
}					t_token;

int					init_lst(t_token *tmp, int size);
int					init_new_node(t_token **tmp, int size);
int					get_next_node(t_token **tmp, t_vars *vars, int i);
void				del_token(t_token **tmp);

#endif
