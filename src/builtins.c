/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/19 18:16:13 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_myprintecho(char *echo, t_tools *tools, int flag)
{
	int	result;

	result = ft_validator(echo);
	if (result == 1)
	{
		write(1, "ERROR\n", 6);
		return ;
	}
	ft_putquotes(echo, tools->env, tools);
	if (flag == 0)
		write(1, "\n", 1);
	return ;
}

static int	ft_myecho(char *echo, t_tools *tools)
{
	int	flag;

	while (*echo == ' ')
		echo++;
	if (ft_strncmp(echo, "echo", 4) == 0)
		echo += 4;
	while (*echo == ' ')
		echo++;
	if (*echo == '-' && *(echo + 1) == 'n')
	{
		while (*echo == '-' || *echo == 'n' || *echo == ' ')
			echo++;
		flag = 1;
	}
	while (*echo == ' ')
		echo++;
	if (*echo == '\0')
	{
		if (flag == 0)
			write(1, "\n", 1);
		return (0);
	}
	ft_myprintecho(echo, tools, flag);
	return (0);
}

t_list	*builtins(void)
{
	t_list			*builtins;
	t_string		*command;
	char			**str;
	unsigned int	i;

	builtins = new_list();
	str = ft_split(BUILTS, ' ');
	i = 0;
	while (str[i] != NULL)
	{
		command = NULL;
		command = terminal_string(str[i]);
		builtins = insert_in_list(builtins, (void *)command);
		string_delete(command);
		free(command);
		i++;
	}
	ft_doublefree(str);
	return (builtins);
}

void	terminator(t_tools *tools, char *prompt, char *built, int blt)
{
	(void)built;
	if (blt == BT_CD)
		ft_mychdir(prompt, tools);
	else if (blt == BT_ECHO)
	{
		if (ft_strlen(prompt) == 4)
			write(1, "\n", 1);
		else
			ft_myecho(prompt, tools);
	}
	else if (blt == BT_EXPORT)
	{
		tools->exp = dup_matrix(tools->env);
		ft_myexport(tools, prompt);
	}
	else if (blt == BT_UNSET)
		ft_myunset(tools->env, prompt);
	else if (blt == BT_ENV)
		ft_myenv(tools->env);
	else if (blt == BT_EXIT)
		ft_void(0);
}
