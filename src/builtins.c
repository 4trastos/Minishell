/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/26 13:10:10 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

static int	ft_myenvp(char *prompt, char *built, t_tools *tools, int len)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (prompt[j] == ' ')
		j++;
	while (i < len)
	{
		if (prompt[j] != built[i])
			return (0);
		i++;
		j++;
	}
	i = 0;
	while (tools->env[i] != NULL)
	{
		printf("%s\n", tools->env[i]);
		i++;
	}
	return (0);
}

static int	ft_myecho(char *str, t_tools *tools)
{
	int		i;
	int		flag;
	char	**echo;

	echo = ft_split(str, ' ');
	i = ft_strlist(echo);
	if (i == 1)
	{
		write(1, "\n", 1);
		ft_doublefree(echo);
		return (0);
	}
	i = 1;
	if (ft_strncmp(echo[i], "-n", 3) == 0)
	{
		if (echo[i + 1] == NULL)
		{
			ft_doublefree(echo);
			return (0);
		}
		flag = 1;
		i++;
	}
	ft_myprintecho(echo, tools, flag, i);
	return (0);
}

static int	ft_findpwd(char *prompt, char *built, t_tools *tools)
{
	int	j;

	(void)built;
	(void)prompt;
	j = 0;
	while (tools->env[j])
	{
		if (ft_strncmp(tools->env[j], "PWD=", 4) == 0)
		{
			printf("%s\n", tools->env[j] + 5);
			return (0);
		}
		j++;
	}
	return (0);
}

t_list	*builtins(void)
{
	t_list			*builtins;
	t_string		*command;
	char			**blts;
	unsigned int	i;

	builtins = new_list();
	blts = ft_split(BUILTS, ' ');
	i = 0;
	while (blts[i] != NULL)
	{
		command = NULL;
		command = terminal_string(blts[i]);
		command->op = OP_BUILTIN;
		builtins = insert_in_list(builtins, (void *)command);
		free(command);
		i++;
	}
	return (builtins);
}

int	terminator(t_tools *tools, char *prompt, char *built, int blt)
{
	if (blt == BT_EXIT)
		return (ft_exit(prompt, built, blt));
	else if (blt == BT_ENV)
		return (ft_myenvp(prompt, built, tools, ft_strlen(built)));
	else if (blt == BT_PWD)
		return (ft_findpwd(prompt, built, tools));
	else if (blt == BT_ECHO)
	{
		if (ft_strlen(prompt) == 4)
		{
			write(1, "\n", 1);
			return (0);
		}
		return (ft_myecho(prompt, tools));
	}
	else if (blt == BT_EXPORT)
		return (ft_myexport(tools->env, prompt, tools));
	else if (blt == BT_UNSET)
		return (ft_myunset(tools->env, prompt));
	else if (blt == BT_CD)
		return (ft_mychdir(prompt));
	return (0);
}

