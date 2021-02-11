/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:01 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/11 13:44:45 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global_vars.h"

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
	t_token		*tmp;
	char		type;
	int			i;

	if (!(parser->list = malloc(sizeof(t_token))))
		del_parser(parser, vars->line, 'a');
	tmp = parser->list;
	if (!(init_lst(tmp, new_strlen(vars->line + 0))))
		del_parser(parser, vars->line, 'a');
	vars->count = 0;
	i = 0;
	while (vars->line[i])
	{
		type = get_token(vars->line[i]);
		if (check_type_token(type, &tmp, vars, &i) == 0)
		{
			tmp = parser->list;
			del_token(&tmp);
			del_parser(parser, vars->line, 'o');
		}
		i++;
	}
	return (0);
}

void	sigint_handler(int n)
{
	write(STDOUT_FILENO, "\b\b  \b\b", 6);
	ft_putendl_fd("", 1);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	(void)n;
}

void	sigquit_handler(int n)
{
	write(STDOUT_FILENO, "\b\b  \b\b", 6);
	(void)n;
}
void	handle_signals()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
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
	while (vars.checker)
	{
		vars.loop = TRUE;
		while (vars.loop)
		{
			vars.loop = FALSE;
			handle_signals();
			ft_putstr_fd(PROMPT, STDOUT_FILENO);
			vars.gnl_check = get_next_line(STDIN_FILENO, &(vars.line));
			if (vars.gnl_check == -1)
				del_parser(parser, vars.line, 'a');
		}
		lexical_analysis(&vars, parser);
		free(vars.line);
		vars.line = NULL;
		g_envp = envp;
		parse(parser, &tree);
		// g_root = tree;
		// envp_create_lst(&g_envlst);
		// executor(tree);
		// free_tree(&tree);
	}
	return (EXIT_SUCCESS);
}
