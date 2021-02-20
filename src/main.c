/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:01 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/20 14:01:01 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**g_envp;

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
	vars.checker = true;
	if (!(parser = malloc(sizeof(t_parser))))
		del_parser(parser, NULL, 'a');
	tree = NULL;
	while (vars.checker)
	{
		vars.loop = true;
		while (vars.loop)
		{
			vars.loop = false;
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
		executor(tree);
	}
	return (EXIT_SUCCESS);
}
