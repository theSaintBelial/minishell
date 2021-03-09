/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:05:51 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/08 23:07:15 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

char	get_token_sec(char c)
{
	if (c == ENTER)
		return (ENTER);
	else if (c == LESS_THEN)
		return (LESS_THEN);
	else if (c == GREATER_THEN)
		return (GREATER_THEN);
	else if (c == C_NULL)
		return (C_NULL);
	return (C_CHAR);
}

char	get_token(char c)
{
	if (c == PIPE)
		return (PIPE);
	else if (c == DOLLAR)
		return (DOLLAR);
	else if (c == F_SLASH)
		return (F_SLASH);
	else if (c == DF_SLASH)
		return (DF_SLASH);
	else if (c == SEMICOLON)
		return (SEMICOLON);
	else if (c == SPACE)
		return (SPACE);
	else if (c == DOUBLE_SLASH)
		return (DOUBLE_SLASH);
	return (get_token_sec(c));
}

/*
** INIT PARSER-LIST
** CHECK EVERY TYPE OF CHAR IN BUFFER (vars->line[i])
** CHECK STATUS OF SPECIAL CHAR OR FORWARD SLASH (lexical_analysis.c)
*/
void	lexical_analysis(t_vars *vars, t_parser *parser)
{
	t_token		*tmp;
	char		type;
	int			i;

	if (!(parser->list = malloc(sizeof(t_token))))
		msg_exit(EXIT_FAILURE, "lexer", "Malloc error");
	tmp = parser->list;
	if (!(init_lst(tmp, new_strlen(vars->line + 0))))
		msg_exit(EXIT_FAILURE, "lexer", "Malloc error");
	vars->count = 0;
	i = -1;
	while (vars->line[++i])
	{
		type = get_token(vars->line[i]);
		if (check_type_token(type, &tmp, vars, &i) == 0)
			msg_exit(EXIT_FAILURE, "lexer", "Malloc error");
	}
	// del_token(&(parser->list));
}
