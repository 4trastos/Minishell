/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/06 14:22:47 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_myprintecho(char **echo, t_tools *tools, int flag, int i)
{
	int	single;
	int	doubles;


	single = 0;
	doubles = 0;
	echo++;
	while (i > 0)
	{
		echo++;
		i--;
	}
	echo--;
	ft_putquotes(echo, tools->env, doubles, single);
	if (flag == 0)
		write(1, "\n", 1);
	return ;
}

static int	ft_myecho(char *str, t_tools *tools)
{
	int		i;
	int		flag;
	char	**echo;

	echo = ft_split(str, ' ');
	if (ft_strlist(echo) == 1)
	{
		write(1, "\n", 1);
		ft_doublefree(echo);
		return (0);
	}
	i = 1;
	flag = 0;
	while (echo[i] != NULL && ft_strncmp(echo[i], "-n", 3) == 0)
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
		free(command);
		i++;
	}
	return (builtins);
}

void	terminator(t_tools *tools, char *prompt, char *built, int blt)
{
	char	**dup;

	dup = NULL;
	(void)built;
	if (blt == BT_CD)
		ft_mychdir(prompt);
	else if (blt == BT_ECHO)
	{
		if (ft_strlen(prompt) == 4)
			write(1, "\n", 1);
		else
			ft_myecho(prompt, tools);
	}
	else if (blt == BT_EXPORT)
	{
		dup = dup_matrix(tools->env);
		if (!dup)
			return ;
		ft_myexport(dup, tools, prompt);
		ft_doublefree(dup);
	}
	else if (blt == BT_UNSET)
		ft_myunset(tools->env, prompt);
}

/* void	ft_myprintecho(char **echo, t_tools *tools, int flag, int i)
{
	int		k;
	int		quotes;
	int		single;
	int		mark;

	k = 0;
	quotes = 0;
	single = 0;
	mark = 0;
	while (echo[k] != NULL)
	{
		ft_isquotes(echo[k], &quotes, &single);
		k++;
	}
	if (single > 1)
		mark = 1;
	ft_writedollar(echo, tools->env, i, mark);
	if (flag == 0)
		write(1, "\n", 1);
	return ;
} */