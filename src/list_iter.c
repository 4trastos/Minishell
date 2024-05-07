/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/07 20:27:30 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

void    list_app_function(t_list *list, t_function f)
{
    unsigned int i;

    if (list != NULL)
    {
        i = 0;
        while (i < list->size)
        {
            f(list->data[i]->str);
            i++;
        }
    }
    else
        write(1, "Error\n", 5);
}

bool    next_iter(t_iterlist *iter)
{
    void    *value;
    
    (void)value;
    if (!iter || !iter->list)
        return (false);
    if (iter->i < iter->list->size)
    {
        iter->i++;
        return (true);   
    }
    iter->value = NULL;
    return (false);
}