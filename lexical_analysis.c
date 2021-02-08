#include "minishell.h"

/*
** CHECK TYPE OF SPECIAL CHAR, STATUS OF FORWARD SLASH IS NORM
** IF type == FORWARD_SLASH ---> CHANGING STATUS OF F_SLASH
*/

int new_strlen(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1 || ft_isdigit(str[i]) == 1)
			len++;
		else if (str[i] == ';' || str[i] == ' ')
			i++;
		else
			return (len);
		i++;
	}
	return (len);
}

int	check_spec_symb(char type, t_token **tmp, t_vars *vars, int *i)
{
	(*i)++;
	while (vars->line[(*i)])
	{
		if (vars->line[(*i)] == type)
		{
			(*tmp)->type = TOKEN;
			return (0);
		}
		(*tmp)->data[vars->count] = vars->line[(*i)];
		vars->count++;
		(*i)++;
	}
	return (0);
}

int	check_spec_symb_sec(char type, t_token **tmp, t_vars *vars, int *i)
{
	(*i)++;
	while (vars->line[(*i)])
	{
		if (vars->line[(*i)++] == DOUBLE_SLASH)
			(*tmp)->data[vars->count] = vars->line[(*i)];
		else
			(*i)--;
		if (vars->line[(*i)] == type)
		{
			(*tmp)->type = TOKEN;
			return (0);
		}
		(*tmp)->data[vars->count] = vars->line[(*i)];
		vars->count++;
		(*i)++;
	}
	return (0);
}

int	another_special_tokens(char type, t_token **tmp, t_vars *vars, int *i)
{
	if (type == C_CHAR)
	{
		(*tmp)->data[vars->count++] = vars->line[(*i)];
		(*tmp)->type = TOKEN;
		return (1);
	}
	if (type == F_SLASH)
	{
		check_spec_symb(type, tmp, vars, i);
	}
	if (type == DF_SLASH)
	{
		check_spec_symb_sec(type, tmp, vars, i);
	}
	if (type == DOUBLE_SLASH)
	{
		(*tmp)->data[vars->count++] = vars->line[++(*i)];
		(*tmp)->type = TOKEN;
		return (0);
	}
	return (0);
}

/*
** CHECK TYPE OF SPECIAL CHAR, STATUS OF FORWARD SLASH IS NORM
** TO INIT NEW NODE ---> struct_init.c
*/

int	check_type_token(char type, t_token **tmp, t_vars *vars, int *i)
{
	if (type == SPACE)
	{
		if (vars->count > 0)
			if (get_next_node(tmp, vars, *i) == 0)
				return (0);
		return (1);
	}
	if (type == SEMICOLON || type == PIPE
	|| type == GREATER_THEN || type == LESS_THEN || type == DOLLAR)
	{
		if (vars->count > 0)
			if (get_next_node(tmp, vars, *i) == 0)
				return (0);
		(*tmp)->data[0] = type;
		(*tmp)->data[1] = '\0';
		(*tmp)->type = type;
		if (!(init_new_node(tmp, new_strlen(vars->line + (*i)))))
			return (0);
		return (1);
	}
	else
		return (another_special_tokens(type, tmp, vars, i));
}
