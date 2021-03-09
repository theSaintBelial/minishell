/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:01 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/09 12:52:15 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "executor.h"
#include "env_lst.h"

t_env	*g_envlst;

void	sigint_handler(int n)
{
	ft_putendl_fd("\b\b  \b\b", STDOUT_FILENO);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	(void)n;
}

void	sigquit_handler(int n)
{
	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
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
	tree = NULL;
	g_envlst = NULL;
	if (!(parser = malloc(sizeof(t_parser))))
		msg_exit(EXIT_FAILURE, "parser", "Malloc error");
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
				msg_exit(EXIT_FAILURE, "get_next_line", "Malloc error");
		}
		lexical_analysis(&vars, parser);
		free(vars.line);
		vars.line = NULL;
		parse(parser, &tree);
yyyyyyyyyyyyyyyyyyyyyyyyyy		if (!g_envlst)
			env_lst_create(&g_envlst, envp);
		executor(tree);
		vars.checker = false;
	}
	env_lst_clear(g_envlst);
	free(parser);
	return (EXIT_SUCCESS);
}
