/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/14 12:11:00 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

void	insert_global(t_list *list, char *command, int numb)
{
	int		i;
	int		len;
	char	*aux;

	write(1, "Entra a guardar builts\n", 23);
	i = 0;
	len = ft_strlen(command) + 1;
	aux = ft_substr(command, i, len);
	write(1, "Crea el nuevo puntero\n", 22);
	list->builtins[numb] = aux;
	write(1, "Sale de guardar builts\n", 23);
}

t_list	*builtins(t_list *list)
{
	int	i;

	i = 0;

	insert_global(list, "exit", i);
	insert_global(list, "cd", (i + 1));
	insert_global(list, "echo", (i + 1));
	insert_global(list, "pwd", (i + 1));
	insert_global(list, "export", (i + 1));
	insert_global(list, "unset", (i + 1));
	insert_global(list, "env", (i + 1));
	return (list);
}
/* void	builtins(t_list *tokens)
{
	int	i;

	i = 0;
	insert_global(tokens, "exit", i);
	insert_global(tokens, "cd", (i + 1));
	insert_global(tokens, "echo", (i + 1));
	insert_global(tokens, "pwd", (i + 1));
	insert_global(tokens, "export", (i + 1));
	insert_global(tokens, "unset", (i + 1));
	insert_global(tokens, "env", (i + 1));
} */

/* t_list	*insert_global(t_list *list, t_string *command)
{
	unsigned int	i;

	i = list->size;
	if (i >= list->builts_numb)
		list = realloc_list(&list, list->builts_numb + INCREASE);
	if (command != NULL)
	{
		list->builtins[i] = terminal_string(command->str);
		list->size++;
	}
	return (list);
} */

/* void	builtins(t_list *tokens)
{
	tokens = insert_global(tokens, terminal_string("exit"));
	tokens = insert_global(tokens, terminal_string("cd"));
	tokens = insert_global(tokens, terminal_string("echo"));
	tokens = insert_global(tokens, terminal_string("pwd"));
	tokens = insert_global(tokens, terminal_string("export"));
	tokens = insert_global(tokens, terminal_string("unset"));
	tokens = insert_global(tokens, terminal_string("env"));
} */