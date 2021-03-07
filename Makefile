# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thesaintbelial <thesaintbelial@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/19 20:16:18 by lgorilla          #+#    #+#              #
#    Updated: 2021/03/05 12:11:04 by thesaintbel      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	minishell
CC				:=	clang
CFLAGS			:=	-g # -Wall -Wextra -Werror
INCLUDES		:=	-I./includes -I./libft/includes
LIBFT			:=	libft.a
LIBFT_DIR		:=	libft
LIBS			:=	-L./$(LIBFT_DIR) -lft
SRCDIR			:=	src
OBJDIR			:=	.obj

UTILS_SRCS		:=	env_lst.c \
					env_lst_add.c \
					errors.c \
					cleaner.c \
					free.c \
					struct_init.c \
					create_tree.c
UTILS_SRCS		:=	$(addprefix utils/, $(UTILS_SRCS))

LEXER_SRCS		:=	lexer.c \
					lexical_analysis.c
LEXER_SRCS		:=	$(addprefix lexer/, $(LEXER_SRCS))

PARSER_SRCS		:=	parse_syntax.c \
					token_checker.c
PARSER_SRCS		:=	$(addprefix parser/, $(PARSER_SRCS))

EXECUTOR_SRCS	:=	executor.c \
					cmd.c \
					builtin.c
EXECUTOR_SRCS	:=	$(addprefix executor/, $(EXECUTOR_SRCS))

SRCS			:=	main.c
SRCS			:=	$(SRCS) $(UTILS_SRCS) $(LEXER_SRCS) $(PARSER_SRCS) $(EXECUTOR_SRCS)
SRCS			:=	$(addprefix src/, $(SRCS))

OBJS			:=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LGREEN			:=	\033[1;32m
WHITE			:=	\033[1;37m
NOC				:=	\033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(LGREEN)Linking $(NAME) - executable$(NOC)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $@
	@echo "$(WHITE)...done$(NOC)"

$(LIBFT):
	@$(MAKE) -C ./$(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
$(OBJDIR):
	@mkdir -p $(dir $(OBJS))

clean:
	@$(MAKE) -C ./$(LIBFT_DIR) clean
	@echo "$(LGREEN)Remove all obj files$(NOC)"
	@rm -rf $(OBJDIR)
	@echo "$(WHITE)...done$(NOC)"
fclean: clean
	@$(MAKE) -C ./$(LIBFT_DIR) fclean
	@echo "$(LGREEN)Remove exec$(NOC)"
	@rm -f $(NAME)
	@echo "$(WHITE)...done$(NOC)"

re: fclean all

.PHONY: all clean fclean re
