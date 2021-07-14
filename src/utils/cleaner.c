/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:55:33 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 19:55:34 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "token_list.h"

void	del_token(t_token **tmp)
{
	if (tmp != NULL && *tmp != NULL)
	{
		if ((*tmp)->data)
			free((*tmp)->data);
		del_token(&(*tmp)->next);
		free((*tmp));
		*tmp = NULL;
	}
}

void	del_parser(t_parser *parser, char *str, char type)
{
	if (str != NULL)
		free(str);
	if (parser != NULL)
	{
		if (type == 'a')
			if (parser->list)
				free(parser->list);
		free(parser);
	}
}
