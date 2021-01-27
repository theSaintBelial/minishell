#include "minishell.h"
/*
** INIT LIST
*/

int init_lst(t_token *tmp, int size)
{
	if (!(tmp->data = ft_calloc(size, sizeof(char))))
	//tmp->data = 0;
	//if (!(tmp->data))
		return 0;
	tmp->type = C_NULL;
	tmp->next = NULL;
	return 1;
}

/*
** INIT NEW NODE OF TOKENS LIST
*/

int init_new_node(t_token **tmp, int size)
{
	if (!((*tmp)->next = malloc(sizeof(t_token))))
		return 0;
	(*tmp) = (*tmp)->next;
	init_lst((*tmp), size);
	return 1;
}

/*
** INIT NEW NODE OF TOKENS LIST
*/

int get_next_node(t_token **tmp, t_vars *vars, int *i)
{
	(*tmp)->data[vars->count] = '\0';
	if (!(init_new_node(tmp, (ft_strlen(vars->line) - (*i)))))
		return 0;
	vars->count = 0;
	return 1;
}
