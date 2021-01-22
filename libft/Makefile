# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/19 20:16:18 by lgorilla          #+#    #+#              #
#    Updated: 2020/08/30 17:58:48 by lgorilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c\
ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c\
ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
ft_strjoin.c ft_strlcat.c  ft_strlen.c ft_strmapi.c\
ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c\
ft_tolower.c ft_toupper.c

SRC_BONUS = ft_lstnew.c ft_lstdelone.c \
ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c

OFILES = ft_atoi.o ft_bzero.o ft_calloc.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o\
ft_isprint.o ft_itoa.o ft_memccpy.o ft_memchr.o ft_memcmp.o\
ft_memcpy.o ft_memmove.o ft_memset.o ft_putchar_fd.o ft_putendl_fd.o\
ft_putnbr_fd.o ft_putstr_fd.o ft_split.o ft_strchr.o\
ft_strjoin.o ft_strlcat.o  ft_strlen.o ft_strmapi.o\
ft_strncmp.o ft_strnstr.o ft_strrchr.o ft_strtrim.o ft_substr.o\
ft_tolower.o ft_toupper.o

OFILES_BONUS = ft_lstnew.o ft_lstdelone.o \
ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o \
ft_lstclear.o ft_lstiter.o ft_lstmap.o

HEADER = libft.h

$(NAME): $(SRC) $(HEADER)
	gcc -Wall -Wextra -Werror -c -I. $(HEADER) $(SRC)
	ar rc $(NAME) $(OFILES)

bonus: $(SRC_BONUS) $(HEADER)
	gcc -Wall -Wextra -Werror -c -I. $(HEADER) $(SRC_BONUS)
	ar rc $(NAME) $(OFILES_BONUS)

all: $(NAME) bonus

clean: 
	rm -f $(OFILES) $(OFILES_BONUS)
fclean: clean 
	rm -f $(NAME)
re: fclean all
