/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 15:37:51 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_myprintecho(char *echo, int flag)
{
	ft_putquotes(echo);
	if (flag == 0)
		write(1, "\n", 1);
	return ;
}

static int	ft_myecho(char *echo)
{
	int	flag;

	while (*echo == ' ')
		echo++;
	if (ft_strncmp(echo, "echo", 4) == 0)
		echo += 4;
	while (*echo == ' ')
		echo++;
	while (*echo == '-' && *(echo + 1) == 'n')
	{
		while (*echo == '-' || *echo == 'n')
			echo++;
		flag = 1;
		while (*echo == ' ')
			echo++;
	}
	if (*echo == '\0')
	{
		if (flag == 0)
			write(1, "\n", 1);
		return (0);
	}
	ft_myprintecho(echo, flag);
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

int	terminator(t_tools *tools, char *prompt, int blt)
{
	int	res;

	res = 0;
	if (blt == BT_CD)
		res = ft_mychdir(prompt, tools);
	else if (blt == BT_ECHO)
	{
		if (ft_strlen(prompt) == 4)
			write(1, "\n", 1);
		else
			res = ft_myecho(prompt);
	}
	else if (blt == BT_EXPORT)
	{
		tools->exp = dup_matrix_envp(tools->env);
		res = ft_myexport(tools, prompt);
	}
	else if (blt == BT_UNSET)
		res = ft_myunset(tools, prompt);
	else if (blt == BT_ENV)
		ft_myenv(tools->env);
	else if (blt == BT_EXIT)
		ft_exit(prompt);
	else if (blt == BT_PWD)
		printf("%s\n", tools->pwd);
	return (res);
}
