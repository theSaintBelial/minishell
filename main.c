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

char	get_token_sec(char c)
{
	if (c == ENTER)
		return (ENTER);
	else if (c == LESS_THEN)
		return (LESS_THEN);
	else if (c == GREATER_THEN)
		return (GREATER_THEN);
	else if (c == C_NULL)
		return (C_NULL);
	return (C_CHAR);
}

char	get_token(char c)
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

int		lexical_analysis(t_vars *vars, t_parser *parser)
{
	t_token 	*tmp;
	char		type;
	int			i;

	if (!(parser->list = malloc(sizeof(t_token))))
		del_parser(parser, vars->line, 'a');
	tmp = parser->list;
	if (!(init_lst(tmp, ft_strlen(vars->line))))
		del_parser(parser, vars->line, 'a');
	vars->count = 0;
	i = 0;
	while (vars->line[i])
	{
		type = get_token(vars->line[i]);
		if (check_type_token(type, &tmp, vars, &i) == 0)
		{
			tmp = parser->list;
			del_token(tmp);
			del_parser(parser, vars->line, 'o');
		}
		i++;
	}
	tmp = parser->list;
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_vars		vars;
	t_parser	*parser;
	t_ast_tree	*tree;

	vars.line = NULL;
	vars.checker = TRUE;
	if (!(parser = malloc(sizeof(t_parser))))
		del_parser(parser, NULL, 'a');
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
				del_parser(parser, vars.line, 'a');
		}
		lexical_analysis(&vars, parser);
		free(vars.line);
		parse(parser, &tree, envp);
		vars.checker = FALSE;
	}
	return (EXIT_SUCCESS);
}