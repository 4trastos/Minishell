/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:18:54 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/04 18:24:10 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_hatedollar(char *str, char **env)
{
	int	index;

	index = 0;
	while (*str != '$' && *str != '\0')
	{
		write(1, &(*str), 1);
		str++;
	}
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
		return ;
	}
	else
		ft_putstr(env[index] + ft_strlen(str) + 1);
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
	// write(1, "\nEsto contiene el token: ", 25);
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	ft_writedollar(char **echo, int flag, char **env, int i)
{
	int	j;

	j = 0;
	while (echo[i] != NULL)
	{
		j = 0;
		if (ft_strchr(echo[i], '$') != NULL)
			ft_hatedollar(echo[i], env);
		else
		{
			while (echo[i][j] != '\0')
			{
				write(1, &echo[i][j], 1);
				j++;
			}
		}
		if (echo[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

void	ft_writestr(char **echo, int flag, char **env, int index)
{
	int	i;

	(void)env;
	i = 0;
	while (echo[index] != NULL)
	{
		i = 0;
		while (echo[index][i] != '\0')
		{
			if (echo[index][i] == '"' || echo[index][i] == 39)
				i++;
			else if (echo[index][i] != '"' && echo[index][i] != 39
				&& echo[index][i] != '\0')
			{
				write(1, &echo[index][i], 1);
				i++;
			}
		}
		write(1, " ", 1);
		index++;
	}
	if (flag == 0)
		printf("\n");
}

/* void	ft_writedollar(char *echo, int flag, char **env, int index)
{
	int	index;

	index = 0;
	echo++;
	index = ft_findenv(env, echo);
	if (index == -1)
		return ;
	printf("%s", env[index] + (ft_strlen(echo) + 1));
	if (flag == 0)
		printf("\n");
} */