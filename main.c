#include "minishell.h"

int err()
{
	ft_putstr_fd("ERROR\n", 1);
	return -1;
}

char get_token_sec(char c)
{
	if (c == ENTER)
		return (ENTER);
	else if (c == LESS_THEN)
		return (LESS_THEN);
	else if (c == GREATER_THEN)
		return (GREATER_THEN);
	else if (c == C_NULL)
		return (C_NULL);
	return C_CHAR;
}

char get_token(char c)
{
	if (c == PIPE)
		return (PIPE);
	else if (c == DOLLAR)
		return (DOLLAR);
	else if (c == F_SLASH)
		return (F_SLASH);
	else if (c == DF_SLASH)
		return (DF_SLASH);
	else if (c == SEMICOLON)
		return (SEMICOLON);
	else if (c == SPACE)
		return (SPACE);
	else if (c == DOUBLE_SLASH)
		return (DOUBLE_SLASH);
	return (get_token_sec(c));
}

/*
** INIT PARSER-LIST
** CHECK EVERY TYPE OF CHAR IN BUFFER (vars->line[i])
** CHECK STATUS OF SPECIAL CHAR OR FORWARD SLASH (lexical_analysis.c)
*/

int lexical_analysis(t_vars *vars, t_parser *parser)
{
	t_token 	*tmp;
	char		type;
	int			i;

	parser->list = malloc(sizeof(t_token));
	tmp = parser->list;
	init_lst(tmp, ft_strlen(vars->line));
	vars->count = 0;
	i = 0;
	while (vars->line[i])
	{
		type = get_token(vars->line[i]);
		check_type_token(type, &tmp, vars, &i);
		i++;
	}
	tmp = parser->list;
	// while (tmp != NULL)
	// {
	// 	printf("%s %c\n", tmp->data, tmp->type);
	// 	tmp = tmp->next;
	// }
	// printf("------------------------\n");
	// exit(0);
	return 0;
}

int main()
{
	t_vars		vars;
	t_parser	*parser;
	t_ast_tree	*tree;

	vars.line = NULL;
	vars.checker = TRUE;
	parser = malloc(sizeof(t_parser));
	tree = NULL;
	while(vars.checker)
	{
		vars.loop = TRUE;
		while (vars.loop)
		{
			vars.loop = FALSE;
			ft_putstr_fd(PROMPT, STDOUT_FILENO);
			vars.gnl_check = get_next_line(STDIN_FILENO, &(vars.line));
			if (vars.gnl_check == -1)
				err();
		}
		lexical_analysis(&vars, parser);
		parse(parser, &tree);
		vars.checker = FALSE;
	}
	return (EXIT_SUCCESS);
}