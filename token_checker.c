#include "minishell.h"

t_ast_tree *pipe_com_node(t_token **tmp)
{

	t_ast_tree *cmd;
	t_ast_tree *left = NULL;
	t_ast_tree *right = NULL;

	check_left_right(&left, tmp);
	if ((*tmp)->type == PIPE)
		(*tmp) = (*tmp)->next;
	if (check_pipe(*tmp) == 1)
		right = pipe_com_node(tmp);
	else
		check_left_right(&right, tmp);
	if (right == NULL || left == NULL)
		return NULL;
	cmd = set_node(NULL, PIPE_N, left, right);
	return cmd;
}

t_ast_tree *lesser_bigger_com_node(t_token **tmp, int type)
{
	t_ast_tree *cmd;
	t_ast_tree *left = NULL;
	t_ast_tree *right = NULL;

	left = arg_case(tmp, NONE);
	if ((*tmp)->type == LESS_THEN || (*tmp)->type == GREATER_THEN)
		(*tmp) = (*tmp)->next;
	if ((*tmp)->type == GREATER_THEN)
		(*tmp) = (*tmp)->next;
	right = arg_case(tmp, NONE);
	if (right == NULL || left == NULL)
		return NULL;
	cmd = set_node(NULL, type, left, right);
	return cmd;
}

int first_case_semicolon(t_token *list)
{
	t_token *current;

	current = list;
	while (current != NULL)
	{
		if (current->type == SEMICOLON)
			return 1;
		current = current->next;
	}
	return 0;
}

int check_pipe(t_token *list)
{
	while (list != NULL)
	{
		if (list->type == SEMICOLON)
			return 0;
		if ((list)->type == PIPE)
		{
			return 1;
		}
		(list) = (list)->next;
	}
	return 0;
}

int check_lesser_bigger(t_token *list)
{
	while (list != NULL)
	{
		if (list->type == SEMICOLON || list->type == PIPE)
			return 0;
		if ((list)->type == LESS_THEN)
			return 1;
		if (list->type == GREATER_THEN)
		{
			if (list->next->type == GREATER_THEN)
				return 3;
			return 2;
		}
		(list) = (list)->next;
	}
	return 0;
}
