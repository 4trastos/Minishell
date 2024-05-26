/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/26 13:03:01 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../incl/minishell.h"
# include <stdbool.h>
# include <limits.h>

# define BUILTS "exit cd echo pwd export unset env"
# define MAX_PATH_LEN 4096

typedef enum s_builtin
{
	BT_NONE,
	BT_EXIT,
	BT_ENV,
	BT_PWD,
	BT_CD,
	BT_ECHO,
	BT_EXPORT,
	BT_UNSET,
}	t_builtin;

typedef enum s_operator
{
	OP_NONE,
	OP_INPUT_REDIRECT,
	OP_OUTPUT_REDIRECT,
	OP_PIPE,
	OP_HERE_DOC,
	OP_OUTPUT_REDIRECT_APPEND,
	OP_DOLLAR_SIGN,
	OP_BUILTIN,
}	t_operator;

typedef struct s_string
{
	unsigned int	size;
	char			*str;
	t_builtin		blt;
	t_operator		op;
}	t_string;

typedef struct s_list
{
	unsigned int	size;
	unsigned int	tokens;
	unsigned int	builts_numb;
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
int			ft_mychdir(char *prompt);
int			ft_findenv(char **env, char *name);
void		ft_addname(char **env, char *name, int index);
void		ft_addvalue(char **env, char *name, int index, char *value);
char		*ft_createname(char *name, char c);
int			ft_strlist(char **echo);
void		ft_doublefree(char **echo);

/*** DELETE ***/

void		string_delete(t_string *string);
void		list_delete(t_list *list);

/*** REALLOC ***/

t_list		*realloc_list(t_list **list, unsigned int new_size);

#endif