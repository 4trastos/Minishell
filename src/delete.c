/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:04:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/07 19:42:38 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

void    string_delete(t_string *string)
{
    string->size = 0;
    free(string->str);
    string->str = NULL;
}

void    list_delete(t_list *list)
{
    list->size = 0;
    list->tokens = 0;
    if (list->data)
        free(list->data);
    list->data = NULL;
    free(list);
}
