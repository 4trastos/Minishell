# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: usuario <usuario@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 16:32:45 by davgalle          #+#    #+#              #
#    Updated: 2024/05/07 19:27:54 by usuario          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address

RM = rm -f

LIB = ar rcs

EXTRA_FLAGS = -lreadline #-lhistory

SRC = src/main.c \
       src/write.c \
	   src/parse.c \
	   src/prompt_loop.c \
	   src/create_lists.c \
	   src/create_lists2.c \
	   src/delete.c \
	   src/pwd.c \
	   src/shlvl.c \
	   src/list_iter.c \
	   utils/matrix_utils.c \
	   utils/minishell_utils.c \
	   utils/minishell_utils_2.c \
	   utils/minishell_convert.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(EXTRA_FLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
