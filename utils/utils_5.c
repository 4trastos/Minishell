/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:43:59 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/22 20:11:04 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_validator_extra(char *echo, int *quotes, int *flag)
{
	int	len;

	len = 0;
	while (*echo != '\0')
	{
		if (*echo == ' ' && *flag == 0)
			*flag = 1;
		else if (*echo != ' ')
		{
			if (*flag == 1)
				ft_void(0);
			*flag = 0;
			if (*echo == '\'' || *echo == '"')
			{
				*quotes = 1;
				if (!ft_checkquote(echo, &len, *echo))
					return (*quotes);
				*quotes = 2;
				echo += len + 1;
			}
		}
		if (*echo != '\0')
			echo++;
	}
	return (*quotes);
}

void	ft_updateprtkn(char *str, unsigned int *i, int result)
{
	if (result == 2)
	{
		while (str[*i] != 92 && str[*i] && str[*i] != '<'
			&& str[*i] != '>' && str[*i] != ';')
			(*i)++;
	}
	else if (result == 0)
	{
		while (str[*i] != 92 && str[*i] != '|' && str[*i]
			&& str[*i] != '<' && str[*i] != '>' && str[*i] != ';')
			(*i)++;
	}
}

char	*updatedollar(char *str)
{
	char	*update;
	int		len;

	(void)update;
	write(1, "Tiene Dollar y tiene que expandir\n", 34);
	len = 0;
	while (str[len] != '$')
		len++;
	while (str[len] != '\0')
	{
		if (str[len] == '$')
			write(1, "Aqui está el expansor\n", 23);
		len++;
	}
	return (str);
}
