#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

# include "gnl/get_next_line.h"
# include "libft/libft.h"

#define				PIPE '|'
#define				DOLLAR '$'
#define				F_SLASH '\''
#define				DF_SLASH '\"'
#define				DOUBLE_SLASH '\\'
#define				SEMICOLON ';'
#define				SPACE ' '
#define				ENTER '\n'
#define				LESS_THEN '<'
#define				GREATER_THEN '>'
#define				QUESTION '?'
#define				C_NULL 0
#define				C_CHAR '/'
#define				TOKEN '-'

#define				PROMPT "\033[1;35mour-minishell$ \033[0m"

/*
** STATUS OF FORWARD SLASH
*/

typedef short		bool;

enum				e_status
{
	STATUS_DF_SLASH,
	STATUS_F_SLASH,
	ORIG_STATUS,
};

enum				e_bool
{
	FALSE,
	TRUE,
};

/*
** AST NODE TYPE
*/

enum 				e_ast_flags
{
	PIPE_N = 1,
	SEMICOLON_N,
	LESS_N,
	GREATER_N,
	D_GREATER_N,
	VARIEBLE_N,
	NONE,
};

/*
** TOKEN DEFINITION
*/

typedef struct s_token
{
	char			*data;
	char			type;
	struct s_token	*next;
}					t_token;

/*
** LIST OF TOKENS
*/

typedef struct s_parser
{
	t_token			*list;
	int				size;
}					t_parser;

typedef struct s_vars
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

typedef struct s_tree
{
	char			*data;
	int			type;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_ast_tree;

typedef struct	s_task
{
	bool		is_pipe_in;
	bool		is_pipe_out;
	int			pipe_in_fd;
	int			pipe_out_fd;
}				t_task;

typedef struct	s_cmd
{
	char	**argv;
	int		argc;
	t_task	*config;
	char	**in_out;
	bool	rewrite;
}				t_cmd;


void				init_lst(t_token *tmp, int size);
int					check_type_token(char type, t_token **tmp, t_vars *vars, int *i);
void				check_all_tokens(t_token **tmp);
void				init_new_node(t_token **tmp, int size);
void				get_next_node(t_token **tmp, t_vars *vars, int *i);
void				check_status(char type, t_token **tmp, t_vars *vars, int i);
int					parse(t_parser *parser, t_ast_tree **tree);
t_ast_tree			*pipe_com_node(t_token **tmp);
t_ast_tree			*lesser_bigger_com_node(t_token **tmp, int type);
int					first_case_semicolon(t_token *list);
int					check_pipe(t_token *list);
int					check_lesser_bigger(t_token *list);
t_ast_tree			*set_node(char *data, int type, t_ast_tree *left, t_ast_tree *right);
t_ast_tree			*get_arg(char *data, t_ast_tree *left, t_ast_tree *right, int type);
t_ast_tree			*arg_case(t_token **lst, int type);
void				check_left_right(t_ast_tree **node, t_token **tmp);

/*
** executor.c
*/
void	executor(t_ast_tree *root_ptr, char **envp_buf);

#endif
