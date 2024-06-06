/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/05 17:42:00 by davgalle         ###   ########.fr       */
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

void	ft_doublefree(char **echo)
{
	int	i;

	i = 0;
	while (echo[i] != NULL)
	{
		free(echo[i]);
		i++;
	}
	free (echo);
}

int	custom_strncmp(char *prompt, char *built, int len, int blt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)blt;
	if (!prompt)
		return (1);
	while (i <= len && built[i] != '\0')
	{
		if (built[i] != prompt[j])
			return (1);
		i++;
		j++;
	}
	return (0);
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
