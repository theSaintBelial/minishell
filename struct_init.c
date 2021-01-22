#include "minishell.h"
/*
** INIT LIST
*/

void init_lst(t_token *tmp, int size)
{
	tmp->data = ft_calloc(size, sizeof(char));
	tmp->type = C_NULL;
	tmp->next = NULL;
}

/*
** INIT NEW NODE OF TOKENS LIST
*/

void init_new_node(t_token **tmp, int size)
{
	(*tmp)->next = malloc(sizeof(t_token));
	(*tmp) = (*tmp)->next;
	init_lst((*tmp), size);
}

/*
** INIT NEW NODE OF TOKENS LIST
*/

void get_next_node(t_token **tmp, t_vars *vars, int *i)
{
	(*tmp)->data[vars->count] = '\0';
	init_new_node(tmp, (ft_strlen(vars->line) - (*i)));
	vars->count = 0;
}
