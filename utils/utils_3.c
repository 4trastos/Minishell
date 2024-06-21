/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/21 17:13:36 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	ft_checkquote(char *echo, int *len, char quote)
{
	char	*end;

	end = NULL;
	echo++;
	end = ft_strchr(echo, quote);
	if (end != NULL)
	{
		*len = end - echo;
		echo = end + 1;
		return (1);
	}
	else
		return (0);
}

int	ft_validator(char *echo)
{
	int		len;
	int		flag;

	len = 0;
	flag = 0;
	while (*echo != '\0')
	{
		if (*echo == ' ' && flag == 0)
			flag = 1;
		else if (*echo != ' ')
		{
			if (flag)
				ft_void(0);
			flag = 0;
			if (*echo == '\'' || *echo == '"')
			{
				if (!ft_checkquote(echo, &len, *echo))
					return (1);
				echo += len + 1;
			}
		}
		if (*echo != '\0')
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

int	ft_get_code(int cod)
{
	while (cod >= 256)
		cod -= 256;
	return (cod);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
