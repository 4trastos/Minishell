/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:04:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/03 13:18:08 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	string_delete(t_string *string)
{
	string->blt = 0;
	string->op = 0;
	string->size = 0;
	free(string->str);
}

void	list_delete(t_list *list)
{
	unsigned int	i;

	i = -1;
	while (++i < list->size)
	{
		string_delete(list->data[i]);
		free(list->data[i]);
	}
	list->value = NULL;
	list->i = 0;
	list->tokens = 0;
	list->size = 0;
	list->builts_numb = 0;
	free(list->data);
	free(list);
}
