/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/07 20:24:52 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

t_string	*parse_strings(char c, char *str, unsigned int *i)
{
    t_string        *new;
    char            *aux;
    unsigned int    start;
    
    start = *i + 1;
    (*i)++;
    while (str[*i] != '\0' && str[*i] != c)
        (*i)++;
    aux = ft_substr(str, start, *i - start);
    new = terminal_string(aux);
    free(aux);
    if (str[*i] == c && str[*i] != '\0')
        (*i)++;
    return (new);    
}

t_string    *parse_operators(char c, char *str, unsigned int *i)
{
    t_string        *new;
    char            *aux;
    unsigned int    start;

    start = *i;
    while (str[*i] == c)
        (*i)++;
    aux = ft_substr(str, start, *i - start);
    new = terminal_string(aux);
    free(aux);
    return (new);
}

t_string    *parse_tokens(char *str, unsigned int *i)
{
    t_string        *new;
    char            *aux;
    unsigned int    start;

    start = *i;
    while (str[*i] != ' ' && str[*i] != '"' && str[*i] != '\'' && str[*i] != '|' && str[*i])
        (*i)++;
    /* if (*i == start)
        return (0); */
    aux = ft_substr(str, start, *i - start);
    new = terminal_string(aux);
    free (aux);
    return (new);
}

t_list  *list_expresion(t_iterlist *iter)
{
    t_list  *aux;
    
    aux = new_list();
    while (next_iter(iter))
    {
        write(1, "Recorriendo los comandos\n", 25);
    }
    return (aux);
}