/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:04:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 18:39:29 by davgalle         ###   ########.fr       */
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

void	list_matrix_delete(t_list **arr_tokens)
{
	unsigned int	i;

	i = 0;
	while (arr_tokens[i] != NULL)
	{
		list_delete(arr_tokens[i]);
		i++;
	}
	free(arr_tokens);
}

void	ft_doublefree(char **echo)
{
	int	i;
	int	len;

	i = 0;
	len = ft_mtx_len(echo);
	while (i <= len && echo[i] != NULL)
	{
		free(echo[i]);
		i++;
	}
	free(echo);
}

void	ft_auxgtf(t_executor *exe, t_tools *tools, char *file)
{
	exe->infile = open(file, O_RDONLY);
	if (exe->infile < 0)
	{
		perror("file");
		ft_empty_doc(exe, tools);
	}
}
