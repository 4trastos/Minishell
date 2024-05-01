# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davgalle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 16:32:45 by davgalle          #+#    #+#              #
#    Updated: 2024/04/30 17:18:33 by davgalle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread

RM = rm -f

LIB = ar rcs

EXTRA_FLAGS = -lreadline #-lhistory

SRC = src/main.c \
       src/write.c \
	   src/parse.c \
	   src/prompt_loop.c \
	   src/create_lists.c \
	   utils/matrix_utils.c \
	   utils/minishell_utils.c

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
