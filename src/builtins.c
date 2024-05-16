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

t_list	*builtins(void)
{
	t_list			*builtins;
	t_string		*command;
	char			**builts;
	unsigned int	i;

	builtins = new_list();
	builts = ft_split(BUILTS, ' ');
	i = 0;
	while (builts[i] != NULL)
	{
		command = NULL;
		command = terminal_string(builts[i]);
		builtins = insert_in_list(builtins, (void *)command);
		free(command);
		i++;
	}
	return (builtins);
}

int	terminator(char *str, t_tools *tools)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "exit", 4) == 0)
		return (EXIT);
	else if (ft_strncmp(str, "env", 3) == 0)
	{
		while (tools->ptr_global->env[i] != NULL)
		{
			printf("%s\n", tools->ptr_global->env[i]);
			i++;
		}
		return (0);
	}
	else
		return (0);
}
