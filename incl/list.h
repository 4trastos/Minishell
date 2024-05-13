/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/13 14:45:49 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../incl/minishell.h"
# include <stdbool.h>

typedef enum s_operator
{
	OP_NONE,
	OP_INPUT_REDIRECT,
	OP_OUTPUT_REDIRECT,
	OP_PIPE,
	OP_HERE_DOC,
	OP_OUTPUT_REDIRECT_APPEND,
}	t_operator;

typedef struct s_string
{
	unsigned int	size;
	char			*str;
	t_operator		op;
}	t_string;

typedef struct s_list
{
	unsigned int	size;
	unsigned int	tokens;
	unsigned int	i;
	void			*value;
	t_string		**data;
}	t_list;

typedef void	(*t_function)(void *);

/*** LIST & NODES ***/

t_list		*new_list(void);
t_string	*terminal_string(char *str);
void		ft_printenvp(char **str);
void		ft_printlist(t_list *tokens);
t_list		*create_tokens(t_string *cmd_input);
t_list		*insert_in_list(t_list *tokens, t_string *command);
void		list_app_function(t_list *list, t_function f);
void		list_expresion(t_list *tokens);

/*** DELETE ***/

void		string_delete(t_string *string);
void		list_delete(t_list *list);

/*** REALLOC ***/

t_list		*realloc_list(t_list **list, unsigned int new_size);

#endif
