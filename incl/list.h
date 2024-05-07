/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/07 20:24:29 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../incl/minishell.h"

typedef struct s_string     //para guardar los comandos que entran por el terminal.
{
    char            *str;
    unsigned int    size;
}   t_string;

typedef struct s_list
{
    unsigned int    size;
    unsigned int    tokens;
//    void            **data;   //para almacenar los tokens (palabras, operadores, etc)
    t_string        **data;   //para almacenar los tokens (palabras, operadores, etc)
}   t_list;

typedef struct s_iterlist
{
    void            *value;
    unsigned int    i;
    t_list          *list;
}   t_iterlist;

typedef void	(*t_function)(void *);  // Aplicar una función a cada elemento de la lista.

/*** LIST & NODES ***/

t_list      *new_list(void);
t_string    *terminal_string(char *str);
void	    ft_printenvp(char **str);
void	    ft_printlist(t_list *tokens);
t_list      *create_tokens(t_string *cmd_input);
t_list      *insert_in_list(t_list *tokens, t_string *command);
void        list_app_function(t_list *list, t_function f);  // Aplicar una función a cada elemento de la lista.
t_iterlist  create_iteri(t_list *list);
t_list      *list_expresion(t_iterlist *iter);

/*** DELETE ***/

void        string_delete(t_string *string);
void        list_delete(t_list *list);

/*** REALLOC ***/

t_list		*realloc_list(t_list **list, unsigned int new_size);

#endif
