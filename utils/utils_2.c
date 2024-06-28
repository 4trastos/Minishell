/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 13:22:25 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_updateprtkn2(char *str, unsigned int *i)
{
	while (str[*i] != 92 && str[*i] != '|' && str[*i]
		&& str[*i] != '<' && str[*i] != '>' && str[*i] != ';'
		&& str[*i] != '\'' && str[*i] != '"' && str[*i] != ' ')
		(*i)++;
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

void	ft_putquotes(char *echo)
{
	while (*echo != '\0')
	{
		write(1, echo, 1);
		echo++;
	}
}
