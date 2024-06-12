/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/12 09:50:43 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "./minishell.h"
# include "./executor.h"
# include <stdbool.h>
# include <limits.h>
# include <stddef.h>

# define BUILTS "cd echo export unset env"
# define MAX_PATH_LEN 4096

typedef struct s_tools	t_tools;

typedef enum s_builtin	t_builtin;

typedef enum s_operator	t_operator;

typedef struct s_string	t_string;

typedef struct s_list	t_list;

typedef void			(*t_function)(void *);

/*** LIST & NODES ***/

t_list		*new_list(void);
t_string	*terminal_string(char *str);
void		ft_printenvp(t_tools *tools);
void		ft_printlist(t_list *tokens);
t_list		*insert_in_list(t_list *tokens, t_string *command);
void		list_app_function(t_list *list, t_function f);
void		list_expresion(t_list *tokens);
int			ft_mychdir(char *prompt, t_tools *tools);
int			ft_findenv(char **env, char *name);
void		ft_addname(t_tools *tools, char *name);
void		ft_addvalue(char **env, char *name, int index);
char		*ft_createname(char *name, char c);
int			ft_strlist(char **echo);
void		ft_doublefree(char **echo);
t_list		*create_tokens(t_list *built, t_tools *tools, t_string *cmd_input);
int			ft_strcmp(char *str1, char *str2);
void		ft_putstr(char *str);
void		ft_updatevalue(char **env, char *name, int index);
void		ft_void(int test);

/*** DELETE ***/

void		string_delete(t_string *string);
void		list_delete(t_list *list);

/*** REALLOC ***/

t_list		*realloc_list(t_list **list, unsigned int new_size);
char		**ft_realloc(char **env, size_t new_size);

#endif