/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:04:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/13 11:19:35 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

void	string_delete(t_string *string)
{
	string->size = 0;
	free(string->str);
	string->str = NULL;
}

void	list_delete(t_list *list)
{
	write(1, "Entra a borrar la lista\n", 24);
	list->size = 0;
	list->tokens = 0;
	if (list->data)
		free(list->data);
	list->data = NULL;
	free(list);
}
