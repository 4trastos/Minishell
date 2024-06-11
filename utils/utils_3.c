/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/11 15:23:16 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_validator(char *echo, char **env)
{
	char	*end;
	int		len;
	int		flag;
	int		test;

	len = 0;
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
					echo = end++;
				}
				else
					return (1);
			}
			else if (*echo == '"')
			{
				echo++;
				end = ft_strchr(echo, '"');
				if (end != NULL)
				{
					len = end - echo;
					echo = end++;
				}
				else
					return (1);
			}
			else if (*echo == '$' && *(echo + 1) != '\0')
			{
				test = ft_testdollar(echo, env);
				if (test == -1)
					return (1);
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
				ft_void(test);
		}
		echo++;
	}
	return (0);
}

char	*ft_updatexport(char *prompt)
{
	while (*prompt == ' ')
		prompt++;
	while (ft_strncmp(prompt, "export", 6) == 0)
		prompt += 6;
	while (*prompt == ' ')
		prompt++;
	return (prompt);
}

