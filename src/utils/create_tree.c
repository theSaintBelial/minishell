/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:40 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/08 23:45:59 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <ft_stdlib.h>
#include <ft_string.h>

void		check_left_right(t_ast_tree **node, t_token **tmp)
{
	if (check_lesser_bigger(*tmp) == 1)
		*node = lesser_bigger_com_node(tmp, LESS_N, NONE, 0);
	else if (check_lesser_bigger(*tmp) == 2)
		*node = lesser_bigger_com_node(tmp, GREATER_N, NONE, 0);
	else if (check_lesser_bigger(*tmp) == 3)
		*node = lesser_bigger_com_node(tmp, D_GREATER_N, NONE, 0);
	else
		*node = arg_case(tmp, NONE);
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

t_ast_tree	*arg_case_sec(t_token **lst, int type)
{
	t_token		*tmp;
	t_ast_tree	*cmd;
	t_ast_tree	*right;

	tmp = *lst;
	if (type == NONE)
		return (arg_case(lst, type));
	if (tmp != NULL && (tmp->type == TOKEN || tmp->type == DOLLAR))
	{
		right = arg_case(&tmp, type);
		cmd = set_node(NULL, type, NULL, right);
		if (tmp->next != NULL)
			*lst = tmp->next;
		return (cmd);
	}
	return (NULL);
}

t_ast_tree	*arg_case(t_token **lst, int type)
{
	t_token		*tmp;
	t_ast_tree	*cmd;
	t_ast_tree	*right;

	tmp = *lst;
	if (tmp != NULL && tmp->type == DOLLAR)
	{
		tmp = tmp->next;
		type = VARIABLE_N;
	}
	else
		type = NONE;
	if (tmp != NULL && tmp->type == TOKEN)
	{
		right = arg_case(&(tmp->next), type);
		cmd = get_arg(tmp->data, NULL, right, type);
		if (tmp->next != NULL)
			*lst = tmp->next;
		return (cmd);
	}
	return (NULL);
}

t_ast_tree	*arg_case_test(t_token *lst, int type)
{
	t_token		*tmp;
	t_ast_tree	*cmd;
	t_ast_tree	*right;

	tmp = lst;
	if (tmp != NULL && tmp->type == DOLLAR)
	{
		tmp = tmp->next;
		type = VARIABLE_N;
	}
	else
		type = NONE;
	if (tmp != NULL && tmp->type == TOKEN)
	{
		right = arg_case_test((tmp->next), type);
		cmd = get_arg(tmp->data, NULL, right, type);
		if (tmp->next != NULL)
			lst = tmp->next;
		return (cmd);
	}
	return (NULL);
}

size_t				ast_len(t_ast_tree *root)
{
	t_ast_tree	*tmp;
	size_t		i;

	i = 0;
	if ((tmp = root))
		while (tmp)
		{
			i++;
			tmp = tmp->right;
		}
	return (i);
}
