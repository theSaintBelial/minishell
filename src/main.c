/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:01 by lgorilla          #+#    #+#             */
/*   Updated: 2021/03/18 22:37:58 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "executor.h"
#include "env_lst.h"

t_env		*g_envlst;
extern int	g_exit_code;

void		sigint_handler(int n)
{
	ft_putendl_fd("\b\b  \b\b", STDOUT_FILENO);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	(void)n;
	g_exit_code = EXIT_FAILURE;
}

void		dfl(int n)
{
	g_exit_code = 128 + n;
	if (n == SIGQUIT)
		ft_putendl_fd("Quit: ", STDOUT_FILENO);
	else if (n == SIGINT)
		ft_putendl_fd("", STDOUT_FILENO);
}

void		default_signals(void)
{
	signal(SIGINT, dfl);
	signal(SIGQUIT, dfl);
}

void		handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int			main(int argc, char **argv, char **envp)
{
	t_vars		vars;
	t_parser	*parser;
	t_ast_tree	*tree;

	(void)argc;
	(void)argv;
	tree = NULL;
	g_envlst = NULL;
	if (!(parser = malloc(sizeof(t_parser))))
		msg_exit(EXIT_FAILURE, "parser", "Malloc error");
	while (true)
	{
		handle_signals();
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		if ((vars.gnl_check = get_next_line(STDIN_FILENO, &(vars.line)) == -1))
			msg_exit(EXIT_FAILURE, "get_next_line", "Malloc error");
		lexical_analysis(&vars, parser);
		free(vars.line);
		parse(parser, &tree);
		(!g_envlst ? env_lst_create(&g_envlst, envp) : 0);
		executor(tree);
	}
	env_lst_clear(g_envlst);
	free(parser);
	return (EXIT_SUCCESS);
}
