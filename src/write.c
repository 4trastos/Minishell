/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:18:54 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/18 10:45:52 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_void(int test)
{
	(void)test;
}

int	ft_testdollar(char *str, char **env)
{
	int	index;

	str++;
	index = ft_findenv(env, str);
	if (index == -1)
	{
		str--;
		return (index);
	}
	return (index);
}

int	ft_hatedollar(char *str, char **env, t_tools *tools)
{
	int	index;

	str++;
	if (*str == '?')
	{
		write(1, ft_itoa(tools->exit_code),
			ft_strlen(ft_itoa(tools->exit_code)));
		return (2);
	}
	index = ft_findenv(env, str);
	if (index == -1)
	{
		str--;
		return (index);
	}
	ft_putstr(ft_strchr(env[index], '=') + 1);
	return (index);
}

void	error_msg(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	exit(1);
}

void	ft_errormsg(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}
