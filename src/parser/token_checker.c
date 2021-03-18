/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:37 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/18 20:14:45 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

extern t_token	*g_node;

t_ast_tree	*pipe_com_node(void)
{
	t_ast_tree *cmd;
	t_ast_tree *left;
	t_ast_tree *right;

	left = NULL;
	right = NULL;
	check_left_right(&left);
	if (g_node->type == PIPE)
		g_node = g_node->next;
	if (check_pipe(g_node) == 1)
		right = pipe_com_node();
	else
		check_left_right(&right);
	if (right == NULL || left == NULL)
		return (free_nodes(&left, &right));
	cmd = set_node(NULL, PIPE_N, left, right);
	return (cmd);
}

t_ast_tree	*lesser_bigger_com_node(t_token *node, int type,
									int ex_type, int flag)
{
	t_ast_tree *left;
	t_ast_tree *right;

	left = NULL;
	right = NULL;
	left = arg_case_sec(g_node, ex_type);
	node = g_node;
	if (node->type == LESS_THEN || node->type == GREATER_THEN)
		g_node = node->next;
	if (g_node->type == GREATER_THEN)
		g_node = g_node->next;
	if (check_lesser_bigger(g_node) == 1)
		right = lesser_bigger_com_node(g_node, LESS_N, type, 1);
	else if (check_lesser_bigger(g_node) == 2)
		right = lesser_bigger_com_node(g_node, GREATER_N, type, 1);
	else if (check_lesser_bigger(g_node) == 3)
		right = lesser_bigger_com_node(g_node, D_GREATER_N, type, 1);
	else
		right = arg_case_sec(g_node, type);
	if (right == NULL || left == NULL)
		return (free_nodes(&left, &right));
	return (set_node(NULL, flag == 0 ? CMD_IO_N : IO_LIST_N, left, right));
}

int			first_case_semicolon(t_token *list)
{
	t_token *current;

	current = list;
	while (current != NULL)
	{
		if (current->type == SEMICOLON)
			return (1);
		current = current->next;
	}
	return (0);
}

int			check_pipe(t_token *list)
{
	while (list != NULL)
	{
		if (list->type == SEMICOLON)
			return (0);
		if ((list)->type == PIPE)
		{
			return (1);
		}
		(list) = (list)->next;
	}
	return (0);
}

int			check_lesser_bigger(t_token *list)
{
	while (list != NULL)
	{
		if (list->type == SEMICOLON || list->type == PIPE)
			return (0);
		if ((list)->type == LESS_THEN)
			return (1);
		if (list->type == GREATER_THEN)
		{
			if (list->next->type == GREATER_THEN)
				return (3);
			return (2);
		}
		(list) = (list)->next;
	}
	return (0);
}
