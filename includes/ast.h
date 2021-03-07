#ifndef AST_H
# define AST_H

#include "token_list.h"

/*
** ABSTRACT SYNTAX TREE
*/
typedef struct		s_tree
{
	char			*data;
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_ast_tree;

t_ast_tree			*command_node(t_token *list, int type);
t_ast_tree			*arg_case_sec(t_token **lst, int type);
t_ast_tree			*set_node(char *data, int type,
									t_ast_tree *left, t_ast_tree *right);
t_ast_tree			*get_arg(char *data, t_ast_tree *left,
									t_ast_tree *right, int type);
t_ast_tree			*arg_case(t_token **lst, int type);
void				check_left_right(t_ast_tree **node, t_token **tmp);
size_t				ast_len(t_ast_tree *root);
void				free_tree(t_ast_tree **root);

#endif
