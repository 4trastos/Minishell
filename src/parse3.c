/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/30 14:46:37 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_updatetspc(char *str)
{
	int	subtract;
	int	i;	

	subtract = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			subtract++;
		if (i != 0 && (str[i] != ' ' && str[i - 1] == ' '))
			subtract--;
		i++;
	}
	return (subtract);
}

void	ft_prstksaux(t_tools *tools, char *str, int start, unsigned int *i)
{
	tools->aux = ft_substr(str, start, *i - start);
	tools->prompt = trimspace(tools->aux);
	tools->prompt = updatedollar(tools->prompt, tools);
	free(tools->aux);
}

void	ft_updatemrtk(char **test, unsigned int *result)
{
	while (*result > 0)
	{
		(*test)++;
		(*result)--;
	}
	*result = 0;
}

void	ft_updtfinaltk(char *aux, unsigned int *result)
{
	char	c;
	char	*end;
	int		len;

	(void)result;
	c = *aux;
	(aux)++;
	end = ft_strchr(aux, c);
	if (end != NULL)
	{
		len = end - aux;
		len = len + 1;
		while (len > 0)
		{
			len--;
			(aux)++;
		}
	}
}

char	**ft_updtmyunst(t_tools *tools, int index)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * ft_mtx_len(tools->env));
	while (tools->env[i] != NULL)
	{
		if (i == index)
			i++;
		if (tools->env[i] != NULL)
		{
			new[j] = ft_strdup(tools->env[i]);
			i++;
			j++;
		}
	}
	new[j] = NULL;
	return (new);
}
