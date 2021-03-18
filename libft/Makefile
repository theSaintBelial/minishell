# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/19 20:16:18 by lgorilla          #+#    #+#              #
#    Updated: 2021/03/13 14:08:06 by lnovella         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	libft.a
CC				:=	clang
CFLAGS			:=	-Wall -Wextra -Werror
INCLUDES		:=	-I./includes
AR				:=	ar -rcs
OBJDIR			:=	.obj

FT_CHAR_SRCS	:=	ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_isprint.c
FT_CHAR_SRCS	:=	$(addprefix ft_char/, $(FT_CHAR_SRCS))

FT_LST_SRCS		:=	ft_lstnew.c \
					ft_lstdelone.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c
FT_LST_SRCS		:=	$(addprefix ft_lst/, $(FT_LST_SRCS))

FT_STDIO_SRCS	:=	ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_putchar_fd.c \
					ft_putendl_fd.c \
					get_next_line.c
FT_STDIO_SRCS	:=	$(addprefix ft_stdio/, $(FT_STDIO_SRCS))

FT_STDLIB_SRCS	:=	ft_atoi.c \
					ft_itoa.c \
					ft_calloc.c
FT_STDLIB_SRCS	:=	$(addprefix ft_stdlib/, $(FT_STDLIB_SRCS))

FT_STRING_SRCS	:=	ft_bzero.c \
					ft_memccpy.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c \
					ft_split.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strmapi.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strtrim.c \
					ft_substr.c
FT_STRING_SRCS	:=	$(addprefix ft_string/, $(FT_STRING_SRCS))

SRCS			:=	$(FT_CHAR_SRCS) $(FT_LST_SRCS) $(FT_STDIO_SRCS) $(FT_STDLIB_SRCS) $(FT_STRING_SRCS)
OBJS			:=	$(SRCS:%.c=$(OBJDIR)/%.o)

LGREEN			:=	\033[1;32m
WHITE			:=	\033[1;37m
NOC				:=	\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(LGREEN)Linking $(NAME) - C static library$(NOC)"
	$(AR) $@ $?
	@echo "$(WHITE)...done$(NOC)"

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
$(OBJDIR):
	@mkdir -p $(OBJDIR)/ft_char
	@mkdir -p $(OBJDIR)/ft_lst
	@mkdir -p $(OBJDIR)/ft_stdio
	@mkdir -p $(OBJDIR)/ft_stdlib
	@mkdir -p $(OBJDIR)/ft_string
clean:
	@echo "$(LGREEN)Remove all obj files$(NOC)"
	@rm -rf $(OBJDIR)
	@echo "$(WHITE)...done$(NOC)"
fclean: clean
	@echo "$(LGREEN)Remove libft.a$(NOC)"
	@rm -f $(NAME)
	@echo "$(WHITE)...done$(NOC)"

re: fclean all

.PHONY: all clean fclean re
