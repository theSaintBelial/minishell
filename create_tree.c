#include "minishell.h"

t_ast_tree	*set_node(char *data, int type, t_ast_tree *left, t_ast_tree *right)
{
	t_ast_tree *cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = type;
	if (data != NULL)
		cmd->data = data;
	cmd->left = left;
	cmd->right = right;
}

t_ast_tree	*get_arg(char *data, t_ast_tree *left, t_ast_tree *right, int type)
{
	t_ast_tree	*cmd;
	char		*str;
	int			i;

	i = ft_strlen(data);
	if (!(str = (char*)malloc(sizeof(char) * i + 1)))
		return NULL;
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

t_ast_tree	*arg_case(t_token **lst, int type)
{
	t_token		*tmp;
	t_ast_tree	*cmd;
	t_ast_tree	*right;

	tmp = *lst;
	if (tmp != NULL && tmp->type == DOLLAR)
	{
		tmp = tmp->next;
		type = VARIEBLE_N;
		get_varieble(&tmp);
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
