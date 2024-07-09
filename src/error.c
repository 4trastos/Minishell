/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/30 13:56:55 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	piticli_boniko(char *str, unsigned int *i, char c, unsigned int *rest)
{
	while (str[*i] == c)
		(*i)++;
	prsopaux(str, i, rest);
	while (istru(c, str[*i]) == 0)
		(*i)++;
}

char	*ft_updateunset(char *prompt)
{
	while (*prompt == ' ')
		prompt++;
	while (ft_strncmp(prompt, "unset", 5) == 0)
		prompt += 5;
	while (*prompt == ' ')
		prompt++;
	return (prompt);
}
