/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/08 21:08:53 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_putquotes(char *echo, char **env, int doubles, int single)
{
	char	*new;
	char	*end;
	int		len;

	(void)doubles;
	(void)single;
	while (*echo != '\0')
	{
		if (*echo == '\'')
		{
			echo++;
			end = ft_strchr(echo, '\'');
			if (end != NULL)
			{
				len = end - echo;
				new = ft_substr(echo, 0, len);
				while (*new != '\0')
				{
					write (1, &(*new), 1);
					new++;
				}
				echo = end + 1;
			}
		}
		if (*echo == '$')
		{
			ft_hatedollar(echo, env);
			break ;
		}
		write(1, &(*echo), 1);
		echo++;
	}
}

void	ft_myenv(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
		{
			ft_putstr(env[i]);
			write(1, "\n", 1);
			i++;
		}
		else
			i++;
	}
}

char	*ft_findhome(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "HOME=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}


/* void	ft_putquotes(char **echo, char **env, int doubles, int single)
{
	int	j;
	int	post_exp;

	while (*echo != NULL)
	{
		j = 0;
		ft_quotescount(*echo, &doubles, &single, &post_exp);
		while ((*echo)[j] != '\0')
		{
			if ((*echo)[j] == '"')
				ft_doubles((*echo)[j], &doubles, &single, &post_exp);
			if ((*echo)[j] == '\'')
				ft_singles((*echo)[j], &doubles, &single, &post_exp);
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
} */

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
} */