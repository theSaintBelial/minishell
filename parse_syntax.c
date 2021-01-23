#include "minishell.h"

void printtree(t_ast_tree *exectree, int t)
{
	if (exectree->left)
		printtree((exectree)->left, t+1);
	// if (exectree != NULL)
	// {
	// 	printtree((exectree)->right, t+1);
		// for (i = 1; i <= t; i++)
		// 	printf(" ");
		printf("\nLevel: %d\n--------------\n", t);
		if (exectree->data)
			printf("%s\n", exectree->data);
		if (exectree->type)
			printf("%d\n", exectree->type);
		if (exectree->right)
			printtree((exectree)->right, t+1);
	// 	printf("%s\n", (exectree)->szData);
	// 	printtree((exectree)->left, t+1);
	// }
}

// // /*
// // ** command arg ; comand arg ; .......
// // */

void check_left_right(t_ast_tree **node, t_token **tmp)
{
	if (check_lesser_bigger(*tmp) == 1)
		*node = lesser_bigger_com_node(tmp, LESS_N);
	else if (check_lesser_bigger(*tmp) == 2)
	 	*node = lesser_bigger_com_node(tmp, GREATER_N);
	else if (check_lesser_bigger(*tmp) == 3)
	 	*node = lesser_bigger_com_node(tmp, D_GREATER_N);
	else
		*node = arg_case(tmp, NONE);
}

void sec_comm_node(t_token **tmp, t_ast_tree **left, t_ast_tree **right, char type)
{
	if (type == 'l')
	{
		if (check_pipe(*tmp) == 1)
			*left = pipe_com_node(tmp);
		else
			check_left_right(left, tmp);
		if ((*tmp)->type == SEMICOLON)
			(*tmp) = (*tmp)->next;
		return ;
	}
	if (type == 'r')
	{
		if (first_case_semicolon(*tmp) == 1)
			*right = command_node(*tmp, SEMICOLON_N);
		else if (check_pipe(*tmp) == 1)
			*right = pipe_com_node(tmp);
		else
			check_left_right(right, tmp);
		return ;	
	}
}

t_ast_tree *command_node(t_token *list, int type)
{
	t_token *tmp;
	t_ast_tree *cmd;
	t_ast_tree *left;
	t_ast_tree *right;

	left = NULL;
	right = NULL;
	tmp = list;
	sec_comm_node(&tmp, &left, &right, 'l');
	if (tmp->next == NULL)
	{
		if (left == NULL)
			return NULL;
		cmd = set_node(NULL, type, left, right);
		return cmd;
	}
	sec_comm_node(&tmp, &left, &right, 'r');
	if (left == NULL || right == NULL)
		return NULL;
	cmd = set_node(NULL, type, left, right);
	return cmd;
}

int	check_grammer(t_token *list, t_ast_tree **tree)
{
	if (first_case_semicolon(list) == 1)
		*tree = command_node(list, SEMICOLON_N);
	else if (check_pipe(list) == 1)
		*tree = pipe_com_node(&list);
	else if (check_lesser_bigger(list) == 1)
		*tree = lesser_bigger_com_node(&list, LESS_N);
	else if (check_lesser_bigger(list) == 2)
	 	*tree = lesser_bigger_com_node(&list, GREATER_N);
	else if (check_lesser_bigger(list) == 3)
	 	*tree = lesser_bigger_com_node(&list, D_GREATER_N);
	else
		*tree = arg_case(&list, NONE);
	if (*tree != NULL)
	{
		printtree(*tree, 0);
		return 1;
	}
	return 0;
}

int	parse(t_parser *parser, t_ast_tree **tree)
{
	t_token 	*tmp;

	tmp = parser->list;
	if (check_grammer(tmp, tree) == 1)
		printf("SUCCESS!\n");
	else
		printf("ERROR\n");
	return 0;
}