
SRCS = 	main.c lexical_analysis.c parse_syntax.c struct_init.c \
		token_checker.c create_tree.c cleaner.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(*.o)

LIBFT_DIR = libft

FLAGS_LINK = libft/libft.a

NAME = minishell

all: $(NAME)

$(NAME): $(SRCS) minishell.h
	make all -C ./libft
	gcc  -Wall -Wextra -Werror -I. minishell.h gnl/get_next_line.h $(SRCS) -L$(LIBFT_DIR) $(FLAGS_LINK) -o $(NAME)

run: @./minishell