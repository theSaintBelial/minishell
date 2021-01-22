#include "minishell.h"

/*
** CHECK TYPE OF SPECIAL CHAR, STATUS OF FORWARD SLASH IS SPECIAL
*/

void check_status(char type, t_token **tmp, t_vars *vars, int i)
{
	if (vars->status == STATUS_DF_SLASH)
	{
		(*tmp)->data[vars->count++] = vars->line[i];
		if (type == DF_SLASH)
			vars->status = ORIG_STATUS;
	}
	else if (vars->status == STATUS_F_SLASH)
	{
		(*tmp)->data[vars->count++] = vars->line[i];
		//else
		//	(*tmp)->data[vars->count++] = vars->line[i];
		if (type == F_SLASH)
			vars->status = ORIG_STATUS;
	}
}

/*
** CHECK TYPE OF SPECIAL CHAR, STATUS OF FORWARD SLASH IS NORM
** IF type == FORWARD_SLASH ---> CHANGING STATUS OF F_SLASH
*/

int another_special_tokens(char type, t_token **tmp, t_vars *vars, int *i)
{
	if (type == F_SLASH)
	{
		vars->status = STATUS_F_SLASH;
		(*tmp)->data[vars->count++] = F_SLASH;
		(*tmp)->type = TOKEN;
		return 0;
	}
	if (type == DF_SLASH)
	{
		vars->status = STATUS_DF_SLASH;
		(*tmp)->data[vars->count++] = DF_SLASH;
		(*tmp)->type = TOKEN;
		return 0;
	}
	if (type == DOUBLE_SLASH)
	{
		(*i)++;
		(*tmp)->data[vars->count++] = vars->line[(*i)];
		(*tmp)->type = TOKEN;
		return 0;
	}
	return 0;
}

/*
** CHECK TYPE OF SPECIAL CHAR, STATUS OF FORWARD SLASH IS NORM
** TO INIT NEW NODE ---> struct_init.c
*/

int check_type_token(char type, t_token **tmp, t_vars *vars, int *i)
{
	if (type == C_CHAR)
	{
		(*tmp)->data[vars->count++] = vars->line[(*i)];
		(*tmp)->type = TOKEN;
		return 0;
	}
	if (type == SPACE)
	{
		if (vars->count > 0)
			get_next_node(tmp, vars, i);
		return 0;
	}
	if (type == SEMICOLON || type == PIPE
	|| type == GREATER_THEN || type == LESS_THEN || type == DOLLAR)
	{
		if (vars->count > 0)
			get_next_node(tmp, vars, i);
		(*tmp)->data[0] = type;
		(*tmp)->data[1] = '\0';
		(*tmp)->type = type;
		init_new_node(tmp, (ft_strlen(vars->line) - (*i)));
		return 0;
	}
	else
		return (another_special_tokens(type, tmp, vars, i));
}