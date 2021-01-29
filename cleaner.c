#include "minishell.h"

void	del_token(t_token *tmp)
{
	if (tmp != NULL)
	{
		if (tmp->data)
			free(tmp->data);
		del_token(tmp->next);
		free(tmp);
	}
}

void	del_parser(t_parser *parser, char *str, char type)
{
	if (str != NULL)
		free(str);
	if (parser != NULL)
	{
		if (type == 'a')
			if (parser->list)
				free(parser->list);
		free(parser);
	}
	ft_putstr_fd("ERROR\n", 1);
	exit(0);
}
