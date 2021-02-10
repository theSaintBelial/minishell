/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:51:16 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/10 20:14:00 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <signal.h>

# define PIPE '|'
# define DOLLAR '$'
# define F_SLASH '\''
# define DF_SLASH '\"'
# define DOUBLE_SLASH '\\'
# define SEMICOLON ';'
# define SPACE ' '
# define ENTER '\n'
# define LESS_THEN '<'
# define GREATER_THEN '>'
# define QUESTION '?'
# define C_NULL 0
# define C_CHAR '/'
# define TOKEN '-'
# define PROMPT "\033[1;35mour-minishell$>\033[0m"

typedef short		bool;

enum				e_bool
{
	TRUE = 1,
	FALSE = 0,
};

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

/*
** TOKEN DEFINITION
*/
typedef struct		s_token
{
	char			*data;
	char			type;
	struct s_token	*next;
}					t_token;

/*
** LIST OF TOKENS
*/
typedef struct		s_parser
{
	t_token			*list;
	int				size;
}					t_parser;

typedef struct		s_vars
{
	char			*line;
	int				status;
	int				count;
	int				gnl_check;
	int				loop;
	int				checker;
}					t_vars;

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

typedef struct	s_dirs
{
	bool		is_in;
	bool		is_out;
	int			in_fd;
	int			out_fd;
}				t_dirs;

typedef struct	s_cmd
{
	char	**argv;
	int		argc;
}				t_cmd;

typedef struct 		s_env
{
	char			*name;
	char			*value;
	int				visible;
	struct s_env	*next;
}					t_env;

extern int			g_exit_code;
extern t_env		*g_envlst;
extern t_ast_tree	*g_root;
extern char			**g_envp;

int					new_strlen(char *str);
int					init_lst(t_token *tmp, int size);
int					check_type_token(char type, t_token **tmp,
									t_vars *vars, int *i);
void				check_all_tokens(t_token **tmp);
int					init_new_node(t_token **tmp, int size);
int					get_next_node(t_token **tmp, t_vars *vars, int i);
int					parse(t_parser *parser, t_ast_tree **tree);
t_ast_tree			*pipe_com_node(t_token **tmp);
t_ast_tree			*lesser_bigger_com_node(t_token **tmp, int type,
									int ex_type, int flag);
int					first_case_semicolon(t_token *list);
int					check_pipe(t_token *list);
int					check_lesser_bigger(t_token *list);
t_ast_tree			*set_node(char *data, int type,
									t_ast_tree *left, t_ast_tree *right);
t_ast_tree			*get_arg(char *data, t_ast_tree *left,
									t_ast_tree *right, int type);
t_ast_tree			*arg_case(t_token **lst, int type);
void				check_left_right(t_ast_tree **node, t_token **tmp);
void				envp_create_lst(t_env **env);
void				del_one_lst(t_env **env, char *name);
void				sort_env_list(t_env *env);
t_env				*ft_env_find(t_env *envlst, char *data_ref);

/*
** file: executor.c
** running all the process
** root_ptr - ptr to the root of the tree
*/
void	executor(t_ast_tree *root_ptr);

t_ast_tree			*command_node(t_token *list, int type);
t_ast_tree			*arg_case_sec(t_token **lst, int type);

/*
** free.c
*/
void				free_tree(t_ast_tree **root);

void				get_variable(t_token **tmp);
void				del_parser(t_parser *parser, char *str, char type);
void				del_token(t_token **tmp);

#endif
