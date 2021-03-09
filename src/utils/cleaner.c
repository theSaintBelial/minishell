/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thesaintbelial <thesaintbelial@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:33 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/07 12:39:43 by thesaintbel      ###   ########.fr       */
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
