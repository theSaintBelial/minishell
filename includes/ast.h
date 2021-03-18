/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:30:37 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 19:33:57 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "token_list.h"

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

t_ast_tree			*command_node(int type);
t_ast_tree			*arg_case_sec(t_token *node, int type);
t_ast_tree			*set_node(char *data, int type,
									t_ast_tree *left, t_ast_tree *right);
t_ast_tree			*get_arg(char *data, t_ast_tree *left,
									t_ast_tree *right, int type);
t_ast_tree			*arg_case(t_token *node);
void				check_left_right(t_ast_tree **node);
size_t				ast_len(t_ast_tree *root);
t_ast_tree			*free_nodes(t_ast_tree **left, t_ast_tree **right);
void				free_tree(t_ast_tree **root);
bool				ft_free(char **ptr);

#endif
