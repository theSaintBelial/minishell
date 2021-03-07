/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:05:47 by lnovella          #+#    #+#             */
/*   Updated: 2021/02/24 20:01:56 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

# include "errors.h"
# include "token_list.h"
# include "parser.h"
# include "minishell.h"

int					new_strlen(char *str);
int					check_type_token(char type, t_token **tmp,
									t_vars *vars, int *i);
int					lexical_analysis(t_vars *vars, t_parser *parser);
char				get_token_sec(char c);
char				get_token(char c);

#endif
