/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/21 16:43:44 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	ft_searchquote(char *str, char **echo, char quote, t_tools *tools)
{
	char	*end;
	char	*new;
	int		test;
	int		i;
	int		len;

	i = 0;
	end = NULL;
	str++;
	end = ft_strchr(str, quote);
	if (end != NULL)
	{
		len = end - str;
		new = ft_substr(str, 0, len);
		if (quote == '\'')
			ft_putstr(new);
		else if (quote == '"')
			ft_doubles(new, &i, &test, tools);
		(*echo) += len + 1;
		free(new);
		return (1);
	}
	return (0);
}

void	ft_cstdoubles(char **echo, char **env, t_tools *tools)
{
	int	test;
	int	i;

	test = ft_hatedollar(*echo, env, tools);
	if (test == -1)
		return ;
	else if (test != 2)
	{
		i = 0;
		while (env[test][i] != '=')
		{
			i++;
			(*echo)++;
		}
	}
	else
		(*echo)++;
}

void	ft_doubles(char *str, int *i, int *test, t_tools *tools)
{
	while (*str != '\0')
	{
		if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '\0')
		{
			*test = ft_hatedollar(str, tools->env, tools);
			if (*test == -1)
				return ;
			else if (*test != 2 && *test != -1)
			{
				while (tools->env[*test][*i] != '=')
				{
					(*i)++;
					str++;
				}
				str++;
			}
			else
				str++;
		}
		write(1, str, 1);
		if (*str != '\0')
			str++;
	}
}

void	ft_putquotes(char *echo, char **env, t_tools *tools, int *space)
{
	while (*echo != '\0')
	{
		if (*echo == ' ' && *space == 0)
			*space = 1;
		else if (*echo != ' ')
		{
			if (*space == 1)
				write(1, " ", 1);
			*space = 0;
			if (*echo == '\'' || *echo == '"')
			{
				if (ft_searchquote(echo, &echo, *echo, tools) == 0)
					return ;
			}
			else if (*echo == '$' && *(echo + 1) != ' ' && *(echo + 1) != '\0')
				ft_cstdoubles(&echo, env, tools);
			else
				write(1, echo, 1);
		}
		echo++;
	}
}
