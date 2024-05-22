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

int	ft_myenvp(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->ptr_global->env[i] != NULL)
	{
		printf("%s\n", tools->ptr_global->env[i]);
		i++;
	}
	return (0);
}

static int	ft_myecho(char *str, t_tools *tools, int len)
{
	int		i;
	int		flag;
	char	**echo;

	if (len == 4)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	flag = 0;
	echo = ft_split(str, ' ');
	if (ft_strncmp(echo[i], "-n", 3) == 0)
	{
		if (echo[i + 1] == NULL)
			return (0);
		flag = 1;
		i++;
	}
	ft_myprintecho(echo, tools, flag, i);
	return (0);
}

/* static int	ft_findpwd(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->ptr_global->env[i])
	{
		if (ft_strncmp(tools->ptr_global->env[i], "PWD=", 4) == 0)
		{
			printf("%s\n", tools->ptr_global->env[i] + 5);
			return (0);
		}
		i++;
	}
	return (0);
} */
static int	ft_findpwd(char *str, t_tools *tools)
{
	int	i;

	i = 3;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	i = 0;
	while (tools->ptr_global->env[i])
	{
		if (ft_strncmp(tools->ptr_global->env[i], "PWD=", 4) == 0)
		{
			printf("%s\n", tools->ptr_global->env[i] + 5);
			return (0);
		}
		i++;
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
		builtins = insert_in_list(builtins, (void *)command);
		free(command);
		i++;
	}
	return (builtins);
}

int	terminator(char *str, t_tools *tools, char *prompt, int blt)
{
	unsigned int	len;

	len = ft_strlen(prompt);
	if ((blt == BT_EXIT) && ft_strncmp(prompt, str, len) == 0)
		return (BT_EXIT);
	else if ((blt == BT_ENV) && ft_strncmp(prompt, str, len) == 0)
		return (ft_myenvp(tools));
	/* else if ((blt == BT_PWD) && ft_strncmp(prompt, str, len) == 0)
		return (ft_findpwd(tools)); */
	else if (blt == BT_PWD)
		return (ft_findpwd(prompt, tools));
	else if (blt == BT_ECHO)
		return (ft_myecho(prompt, tools, ft_strlen(prompt)));
	else if (blt == BT_EXPORT)
		return (ft_myexport(tools->ptr_global->env, prompt, tools));
	else if (blt == BT_UNSET)
		return (ft_myunset(tools->ptr_global->env, prompt));
	else if (blt == BT_CD)
		return (ft_mychdir(prompt));
	return (0);
}
