/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/13 15:17:42 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

void	list_app_function(t_list *list, t_function f)
{
	unsigned int	i;

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

bool	next_string(t_list *tokens, unsigned int *i)
{
	void	*value;

	if (!tokens || !tokens->data)
		return (false);
	if ((*i) < tokens->size)
	{
		value = tokens->data[(*i)]->str;
		(*i)++;
		tokens->value = value;
		return (true);
	}
	tokens->value = NULL;
	return (false);
}
