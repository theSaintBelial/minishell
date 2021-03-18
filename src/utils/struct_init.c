/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:28 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/18 19:54:10 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_list.h"
#include "lexer.h"
#include <ft_stdlib.h>

/*
** INIT LIST
*/

int		init_lst(t_token *tmp, int size)
{
	if (!(tmp->data = (char *)ft_calloc(size + 1, sizeof(char))))
		return (0);
	tmp->type = C_NULL;
	tmp->next = NULL;
	return (1);
}

/*
** INIT NEW NODE OF TOKENS LIST
*/

int		init_new_node(t_token **tmp, int size)
{
	t_token		*cur;

	cur = (*tmp);
	(*tmp) = (*tmp)->next;
	if (!((*tmp) = (t_token *)malloc(sizeof(t_token))))
		return (0);
	cur->next = (*tmp);
	if ((init_lst((*tmp), size)) == 0)
		return (0);
	return (1);
}

/*
** GET NEXT NODE OF TOKENS LIST
*/

int		get_next_node(t_token **tmp, t_vars *vars, int i)
{
	i++;
	if (!(init_new_node(tmp, new_strlen(vars->line + i))))
		return (0);
	vars->count = 0;
	return (1);
}
