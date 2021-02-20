/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:37 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/19 13:21:24 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

t_ast_tree	*pipe_com_node(t_token **tmp)
{

	t_ast_tree *cmd;
	t_ast_tree *left;
	t_ast_tree *right;

	left = NULL;
	right = NULL;
	check_left_right(&left, tmp);
	if ((*tmp)->type == PIPE)
		(*tmp) = (*tmp)->next;
	if (check_pipe(*tmp) == 1)
		right = pipe_com_node(tmp);
	else
		check_left_right(&right, tmp);
	if (right == NULL || left == NULL)
		return (NULL);
	cmd = set_node(NULL, PIPE_N, left, right);
	return (cmd);
}

t_ast_tree	*lesser_bigger_com_node(t_token **tmp, int type,
									int ex_type, int flag)
{
	t_ast_tree *cmd;
	t_ast_tree *left;
	t_ast_tree *right;

	left = NULL;
	right = NULL;
	left = arg_case_sec(tmp, ex_type);
	if ((*tmp)->type == LESS_THEN || (*tmp)->type == GREATER_THEN)
		(*tmp) = (*tmp)->next;
	if ((*tmp)->type == GREATER_THEN)
		(*tmp) = (*tmp)->next;
	if (check_lesser_bigger(*tmp) == 1)
		right = lesser_bigger_com_node(tmp, LESS_N, type, 1);
	else if (check_lesser_bigger(*tmp) == 2)
		right = lesser_bigger_com_node(tmp, GREATER_N, type, 1);
	else if (check_lesser_bigger(*tmp) == 3)
		right = lesser_bigger_com_node(tmp, D_GREATER_N, type, 1);
	else
		right = arg_case_sec(tmp, type);
	if (right == NULL || left == NULL)
		return (NULL);
	if (flag == 0)
		return (cmd = set_node(NULL, CMD_IO_N, left, right));
	else
		return (cmd = set_node(NULL, IO_LIST_N, left, right));
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
