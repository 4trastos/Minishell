/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:18:54 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/06 18:45:39 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_hatedollar(char *str, char **env)
{
	int		index;

	while (*str == 39 || *str == '\"')
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

/* void ft_writedollar(char **echo, char **env, int doubles, int single)
{
	int	j;

	while (*echo != NULL)
	{
		j = 0;
		while ((*echo)[j] != '\0')
		{
			if ((*echo)[j] == '\'')
			{
				if (!doubles)
					single = !single;
				else
					write(1, &(*echo)[j], 1);
			}
			else if ((*echo)[j] == '"')
			{
				if (!single)
					doubles = !doubles;
				else
					write(1, &(*echo)[j], 1);
			}
			else if ((*echo)[j] == '$' && !single)
			{
				ft_hatedollar(*echo, env);
				while ((*echo)[j] && (ft_isalnum((*echo)[j])
					|| (*echo)[j] == '_'))
					j++;
				break ;
			}
			else
				write(1, &(*echo)[j], 1);
			j++;
		}
		if ((*echo)++ != NULL)
			write(1, " ", 1);
		echo++;
	}
} */
