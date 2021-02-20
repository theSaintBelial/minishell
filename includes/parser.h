#ifndef PARSER_H
# define PARSER_H

# include "token_list.h"
# include "ast.h"

/*
** AST NODE TYPE
*/
enum				e_ast_flags
{
	PIPE_N = 1,
	SEMICOLON_N,
	LESS_N,
	GREATER_N,
	D_GREATER_N,
	CMD_IO_N,
	IO_LIST_N,
	VARIABLE_N,
	NONE,
};

typedef struct		s_parser
{
	t_token			*list;
	int				size;
}					t_parser;

int					parse(t_parser *parser, t_ast_tree **tree);
int					check_lesser_bigger(t_token *list);
t_ast_tree			*pipe_com_node(t_token **tmp);
t_ast_tree			*lesser_bigger_com_node(t_token **tmp, int type,
									int ex_type, int flag);
int					first_case_semicolon(t_token *list);
int					check_pipe(t_token *list);
void				del_parser(t_parser *parser, char *str, char type);

#endif
