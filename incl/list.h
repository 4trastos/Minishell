/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/27 10:44:08 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "./minishell.h"
# include "./executor.h"
# include <stdbool.h>
# include <limits.h>
# include <stddef.h>

# define BUILTS "cd echo export unset env exit"
# define MAX_PATH_LEN 4096

typedef struct s_tools	t_tools;

typedef enum s_builtin	t_builtin;

typedef enum s_operator	t_operator;

typedef struct s_string	t_string;

typedef struct s_list	t_list;

typedef void			(*t_function)(void *);

/*** LIST & NODES ***/

t_list		*new_list(void);
t_list		*create_tokens(t_list *built, t_tools *tools, t_string *cmd_input);
t_list		*insert_in_list(t_list *tokens, t_string *command);
t_string	*terminal_string(char *str);
char		*ft_createname(char *name, char c);
char		*ft_searchqu(char *str, char c, unsigned int *i, t_tools *tools);
char		*ft_moretoken(char *str, unsigned int *i, t_tools *tools);
void		ft_printenvp(t_tools *tools);
void		ft_printlist(t_list *tokens);
void		list_app_function(t_list *list, t_function f);
void		list_expresion(t_list *tokens);
void		ft_addname(t_tools *tools, char *name);
void		ft_addvalue(char **env, char *name, int index);
void		ft_putstr(char *str);
void		ft_updatevalue(char **env, char *name, int index);
void		ft_void(int test);
void		ft_doubles(char *str, int *i, int *test, t_tools *tools);
void		ft_cstdoubles(char **echo, char **env, t_tools *tools);
int			ft_strlist(char **echo);
int			ft_strcmp(char *str1, char *str2);
int			ft_mychdir(char *prompt, t_tools *tools);
int			ft_findenv(char **env, char *name);
int			custom_strnstr(char *str, char *built);
void		ft_iterone(char *str, t_tools *tools, int *add, int *subtract);
char		*ft_itertwo(char *update, char *str, t_tools *tools);
char		*ft_updatetokens(char *str, unsigned int *i, t_tools *tools);
void		ft_finaltoken(char *test, unsigned int *result);
void		ft_updatepdll(char *str, char c, unsigned int *i,
				unsigned int *flag);
void		ft_upupdatetk(char *str, char **test, unsigned int *i);
char		*ft_updatemoretk(char *new, char *test, unsigned int *i,
				t_tools *tools);
char		*prsstraux(char *aux, char *str, unsigned int *i, t_tools *tools);
void		prsopaux(char *str, unsigned int *i, unsigned int *rest);
int			istru(char c, char actual);
void		addblt(t_string *new, int flag);

/*** DELETE ***/

void		string_delete(t_string *string);
void		list_delete(t_list *list);
void		list_matrix_delete(t_list **arr_tokens);
void		ft_doublefree(char **echo);

/*** REALLOC ***/

t_list		*realloc_list(t_list **list, unsigned int new_size);
char		**ft_realloc(char **env, size_t new_size);

#endif