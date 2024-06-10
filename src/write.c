/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:18:54 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/10 13:28:30 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_hatedollar(char *str, char **env)
{
	int	index;

	str++;
	index = ft_findenv(env, str);
	if (index == -1)
	{
		str--;
		while (*str != '\0')
		{
			write(1, &(*str), 1);
			str++;
		}
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

/* void	ft_hatedollar(char *str, char **env)
{
	int		index;

	while (*str == '\"')
		str++;
	while (*str != '$' && *str != '\0')
	{
		write(1, &(*str), 1);
		str++;
	}
	str++;
	if (*str == '\0')
		return (ft_putstr(str - 1));
	index = ft_findenv(env, str);
	if (index == -1)
	{
		str--;
		while (*str != '\0')
		{
			write(1, &(*str), 1);
			str++;
		}
		return ;
	}
	else
		ft_putstr(ft_strchr(env[index], '=') + 1);
} */
