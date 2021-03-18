/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:21 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/18 20:11:03 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

t_token		*g_node;

void		sec_comm_node(t_ast_tree **left,
							t_ast_tree **right, char type)
{
	if (type == 'l')
	{
		if (check_pipe(g_node) == 1)
			*left = pipe_com_node();
		else
			check_left_right(left);
		if (g_node->type == SEMICOLON)
			g_node = g_node->next;
		if (g_node->type != TOKEN)
			g_node = g_node->next;
		return ;
	}
	if (type == 'r')
	{
		if (first_case_semicolon(g_node) == 1)
			*right = command_node(SEMICOLON_N);
		else if (check_pipe(g_node) == 1)
			*right = pipe_com_node();
		else
			check_left_right(right);
		return ;
	}
}

t_ast_tree	*command_node(int type)
{
	t_ast_tree		*cmd;
	t_ast_tree		*left;
	t_ast_tree		*right;

	left = NULL;
	right = NULL;
	sec_comm_node(&left, &right, 'l');
	if (g_node == NULL)
	{
		if (left == NULL)
			return (NULL);
		cmd = set_node(NULL, SEMICOLON_N, left, NULL);
		return (cmd);
	}
	sec_comm_node(&left, &right, 'r');
	if (left == NULL || right == NULL)
		return (free_nodes(&left, &right));
	cmd = set_node(NULL, type, left, right);
	return (cmd);
}

int			check_grammer(t_ast_tree **tree)
{
	if (first_case_semicolon(g_node) == 1)
		*tree = command_node(SEMICOLON_N);
	else if (check_pipe(g_node) == 1)
		*tree = pipe_com_node();
	else if (check_lesser_bigger(g_node) == 1)
		*tree = lesser_bigger_com_node(g_node, LESS_N, NONE, 0);
	else if (check_lesser_bigger(g_node) == 2)
		*tree = lesser_bigger_com_node(g_node, GREATER_N, NONE, 0);
	else if (check_lesser_bigger(g_node) == 3)
		*tree = lesser_bigger_com_node(g_node, D_GREATER_N, NONE, 0);
	else
		*tree = arg_case(g_node);
	if (*tree != NULL)
		return (1);
	return (0);
}

int			parse(t_parser *parser, t_ast_tree **tree)
{
	g_node = parser->list;
	if (check_grammer(tree) == 1)
		del_token(&parser->list);
	else
	{
		del_token(&parser->list);
		free_tree(tree);
		return (msg_return(1, "parser", "Syntax error"));
	}
	return (0);
}
