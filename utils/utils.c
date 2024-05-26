/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/24 13:03:10 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

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
	if (!prompt)
		return (1);
	while (prompt[j] == ' ')
		j++;
	while (i <= len && built[i] != '\0')
	{
		if (built[i] != prompt[j])
			return (1);
		i++;
		j++;
	}
	while (prompt[j] != '\0')
	{
		if (prompt[j] != ' ' && blt < 4)
			return (1);
		j++;
	}
	return (0);
}

