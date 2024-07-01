/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:42:21 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/01 09:40:55 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_list	*new_list(void)
{
	t_list			*new;
	unsigned int	capacity;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	capacity = 10;
	new->data = (t_string **)malloc(sizeof(t_string *) * capacity);
	if (!new->data)
		return (NULL);
	new->size = 0;
	new->tokens = capacity;
	return (new);
}

t_string	*terminal_string(char *str)
{
	t_string		*new;
	unsigned int	i;

	new = (t_string *)malloc(sizeof(t_string));
	if (!new)
		return (NULL);
	i = 0;
	new->size = ft_strlen(str);
	new->str = (char *)malloc(sizeof(char) * (new->size + 1));
	if (!new->str)
		return (NULL);
	while (str[i] != '\0')
	{
		new->str[i] = str[i];
		i++;
	}
	new->str[i] = '\0';
	return (new);
}

t_list	*insert_in_list(t_list *list, t_string *command)
{
	unsigned int	i;

	i = list->size;
	if (i >= list->tokens)
		list = realloc_list(&list, list->tokens + INCREASE);
	if (command != NULL)
	{
		list->data[i] = terminal_string(command->str);
		list->data[i]->op = command->op;
		list->data[i]->blt = command->blt;
		list->size++;
	}
	return (list);
}

t_list	*realloc_list(t_list **list, unsigned int increase)
{
	t_list			*new;
	unsigned int	i;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->size = (*list)->size;
	new->tokens = increase;
	new->data = (t_string **)malloc(sizeof(t_string *) * increase);
	if (!new->data)
		return (NULL);
	i = 0;
	while (i < (*list)->size)
	{
		new->data[i] = terminal_string((*list)->data[i]->str);
		i++;
	}
	free((*list)->data);
	free(*list);
	return (new);
}

t_list	*create_tokens(t_list *built, t_tools *tools, t_string *cmd_input)
{
	t_list			*tokens;
	t_string		*command;
	char			*str;
	unsigned int	i;

	tokens = new_list();
	str = cmd_input->str;
	i = 0;
	while (str[i] != '\0')
	{
		command = ft_prcplt(built, tools, str, &i);
		if (!command)
		{
			list_delete(tokens);
			free(command);
			return (write(2, "Parse ERROR\n", 12), NULL);
		}
		tokens = insert_in_list(tokens, command);
		string_delete(command);
		free(command);
	}
	return (tokens);
}
