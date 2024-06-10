/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/10 13:52:51 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	ft_doubles(char *str, char **env, int *test)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		if (*str == '$')
		{
			*test = ft_hatedollar(str, env);
			if (*test == -1)
				return ;
			else
			{
				while (env[*test][i] != '=')
				{
					i++;
					str++;
				}
				str++;
			}
		}
		write(1, &(*str), 1);
		str++;
	}
}

void	ft_putquotes(char *echo, char **env, int doubles, int single)
{
	char	*new;
	char	*end;
	int		len;
	int		flag;
	int		test;

	(void)doubles;
	(void)single;
	flag = 0;
	while (*echo != '\0')
	{
		if (*echo == ' ' && flag == 0)
			flag = 1;
		else if (*echo != ' ')
		{
			if (flag)
				write(1, " ", 1);
			flag = 0;
			if (*echo == '\'')
			{
				echo++;
				end = ft_strchr(echo, '\'');
				if (end != NULL)
				{
					len = end - echo;
					new = ft_substr(echo, 0, len);
					ft_putstr(new);
					echo = end++;
				}
				else
				{
					write(1, "Error", 5);
					return ;
				}
			}
			else if (*echo == '"')
			{
				echo++;
				end = ft_strchr(echo, '"');
				if (end != NULL)
				{
					len = end - echo;
					new = ft_substr(echo, 0, len);
					ft_doubles(new, env, &test);
					echo = end++;
				}
				else
				{
					write(1, "Error", 5);
					return ;
				}
			}
			else if (*echo == '$' && *(echo + 1) != '\0')
			{
				ft_doubles(echo, env, &test);
				if (test != -1)
				{
					int i = 0;
					while (++i <= 4)
						echo++;
				}
			}
			else
				write(1, &(*echo), 1);
		}
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