/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/12 10:59:14 by davgalle         ###   ########.fr       */
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
		write(1, str, 1);
		if (*str != '\0')
			str++;
	}
}

void	ft_putquotes(char *echo, char **env)
{
	char	*new;
	char	*end;
	int		len;
	int		flag;
	int		test;

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
					free(new);
				}
				else
					return ;
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
					free(new);
				}
				else
					return ;
			}
			else if (*echo == '$' && *(echo + 1) != '\0')
			{
				test = ft_hatedollar(echo, env);
				if (test == -1)
					return ;
				else
				{
					len = 0;
					while (env[test][len] != '=')
					{
						len++;
						echo++;
					}
				}
			}
			else
				write(1, echo, 1);
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
