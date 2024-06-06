/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/06 19:29:24 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	ft_doubles(char c, int *doubles, int *single)
{
	if (c == '"')
	{
		if (!*single)
			*doubles = !*doubles;
		else
			write(1, &c, 1);
	}
	else
		write(1, &c, 1);
}

static void	ft_singles(char c, int *doubles, int *single)
{
	if (c == '\'')
	{
		if (!*doubles)
			*single = !*single;
		else
			write(1, &c, 1);
	}
	else
		write(1, &c, 1);
}

void	ft_putquotes(char **echo, char **env, int doubles, int single)
{
	int	j;

	while (*echo != NULL)
	{
		j = 0;
		while ((*echo)[j] != '\0')
		{
			if ((*echo)[j] == '\'')
				ft_singles((*echo)[j], &doubles, &single);
			if ((*echo)[j] == '"')
				ft_doubles((*echo)[j], &doubles, &single);
			else if ((*echo)[j] == '$')
			{
				ft_isquotes(&(*echo)[j], env, &doubles, &single);
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
}


/* static void	ft_doubles(char c, int *doubles, int *single)
{
	if (c == '"')
	{
		if (!*single)
			*doubles = !*doubles;
		else
			write(1, &c, 1);
	}
	else
		write(1, &c, 1);
}

static void	ft_singles(char c, int *doubles, int *single)
{
	if (c == '\'')
	{
		if (!*doubles)
			*single = !*single;
		else
			write(1, &c, 1);
	}
	else
		write(1, &c, 1);
}

void	ft_putquotes(char **echo, char **env, int doubles, int single)
{
	int	j;

	while (*echo != NULL)
	{
		j = 0;
		while ((*echo)[j] != '\0')
		{
			if ((*echo)[j] == '\'')
				ft_singles((*echo)[j], &doubles, &single);
			if ((*echo)[j] == '"')
				ft_doubles((*echo)[j], &doubles, &single);
			else if ((*echo)[j] == '$')
			{
				ft_isquotes(*echo, env, &doubles, &single);
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
