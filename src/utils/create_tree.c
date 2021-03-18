/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:40 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/18 19:54:52 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <ft_stdlib.h>
#include <ft_string.h>

extern t_token		*g_node;

void		check_left_right(t_ast_tree **node)
{
	if (check_lesser_bigger(g_node) == 1)
		*node = lesser_bigger_com_node(g_node, LESS_N, NONE, 0);
	else if (check_lesser_bigger(g_node) == 2)
		*node = lesser_bigger_com_node(g_node, GREATER_N, NONE, 0);
	else if (check_lesser_bigger(g_node) == 3)
		*node = lesser_bigger_com_node(g_node, D_GREATER_N, NONE, 0);
	else
		*node = arg_case(g_node);
}

t_ast_tree	*set_node(char *data, int type, t_ast_tree *left, t_ast_tree *right)
{
	t_ast_tree *cmd;

	if (!(cmd = malloc(sizeof(*cmd))))
		msg_exit(EXIT_FAILURE, "parser", ERR_MALLOC);
	cmd->type = type;
	cmd->data = data;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}

t_ast_tree	*get_arg(char *data, t_ast_tree *left, t_ast_tree *right, int type)
{
	t_ast_tree	*cmd;
	char		*str;
	size_t		i;

	i = ft_strlen(data);
	if (!(str = (char*)ft_calloc(i + 1, sizeof(char))))
		msg_exit(EXIT_FAILURE, "parser", ERR_MALLOC);
	ft_strlcpy(str, data, i + 1);
	cmd = set_node(str, type, left, right);
	return (cmd);
}

t_ast_tree	*arg_case_sec(t_token *node, int type)
{
	t_ast_tree	*cmd;
	t_ast_tree	*right;

	if (type == NONE)
		return (arg_case(node));
	if (node != NULL && (node->type == TOKEN || node->type == DOLLAR))
	{
		right = arg_case(node);
		cmd = set_node(NULL, type, NULL, right);
		if (node->next != NULL)
			g_node = node->next;
		return (cmd);
	}
	return (NULL);
}

t_ast_tree	*arg_case(t_token *node)
{
	t_ast_tree	*cmd;
	t_ast_tree	*right;
	int			type;

	if (node != NULL && node->type == DOLLAR)
	{
		node = node->next;
		type = VARIABLE_N;
	}
	else
		type = NONE;
	if (node != NULL && node->type == TOKEN)
	{
		g_node = node->next;
		right = arg_case(node->next);
		cmd = get_arg(node->data, NULL, right, type);
		return (cmd);
	}
	return (NULL);
}
