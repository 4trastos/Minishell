/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/20 11:06:25 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_strlist(char **echo)
{
	int	i;

	i = 0;
	while (echo[i] != NULL)
		i++;
	return (i);
}

int	custom_strnstr(char *str, char *built)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (1);
	while (built[i] != '\0')
	{
		if (built[i] != str[j])
			return (1);
		i++;
		j++;
	}
	if (str[j] == '\0' || str[j] == ' ')
		return (0);
	return (1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	write_env(char *env, int fd)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	i++;
	while (env[i] != '\0' && env[i])
	{
		write(fd, &env[i], 1);
		i++;
	}
}
