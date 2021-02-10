/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:40 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/10 20:22:09 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (NULL);
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
	int			i;

	i = ft_strlen(data);
	if (!(str = (char*)ft_calloc(i + 1, sizeof(char))))
		return (NULL);
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
