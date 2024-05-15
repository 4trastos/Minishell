# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 16:32:45 by davgalle          #+#    #+#              #
#    Updated: 2024/05/15 10:46:55 by davgalle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

RM = rm -f

LIB = ar rcs

EXTRA_FLAGS = -lreadline #-lhistory

SRC = src/main.c \
		src/write.c \
		src/parse.c \
		src/parse2.c \
		src/prompt_loop.c \
		src/create_lists.c \
		src/builtins.c \
		src/delete.c \
		src/pwd.c \
		src/shlvl.c \
		src/list_iter.c \
		src/operator.c \
		src/executor.c \
		src/here_doc.c \
		src/gnl.c \
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
