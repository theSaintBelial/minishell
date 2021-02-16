# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 18:51:08 by lgorilla          #+#    #+#              #
#    Updated: 2021/02/15 17:01:23 by lnovella         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	main.c lexical_analysis.c parse_syntax.c struct_init.c \
		token_checker.c create_tree.c executor.c free.c cleaner.c \
		env_list.c sort_env_list.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c error.c

OBJS = $(*.o)

LIBFT_DIR = libft

FLAGS_LINK = libft/libft.a

NAME = minishell

all: $(NAME)

$(NAME): $(SRCS)
	make all -C ./libft
	gcc -g -I. gnl/get_next_line.h $(SRCS) -L$(LIBFT_DIR) $(FLAGS_LINK) -o $(NAME)

run: @./minishell
