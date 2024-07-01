/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lists2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/01 09:30:17 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	**ft_realloc(char **env, size_t new_size)
{
	char	**new;
	int		i;

	new = malloc(new_size);
	if (!new)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		new[i] = env[i];
		i++;
	}
	new[i] = NULL;
	free(env);
	return (new);
}

char	*ft_updatetokens(char *str, unsigned int *i, t_tools *tools)
{
	char			*aux;
	char			*test;
	unsigned int	result;
	unsigned int	start;	

	test = str;
	start = *i;
	result = *i;
	while (result > 0)
	{
		test++;
		result--;
	}
	ft_finaltoken(test, &result);
	ft_updateprtkn2(str, i);
	aux = ft_substr(str, start, *i - start);
	while (result > 0)
	{
		aux = prsstraux(aux, str, i, tools);
		result--;
	}
	return (aux);
}

char	*ft_moretoken(char *str, unsigned int *i, t_tools *tools)
{
	char			*new;
	char			*test;
	char			*txuru;
	unsigned int	result;
	int				space;

	space = 0;
	test = str;
	result = *i;
	new = NULL;
	ft_updatemrtk(&test, &result);
	space = ft_fluki(&test, i);
	if (*test == '\'' || *test == '"')
		new = ft_searchqu(test, *test, i, tools);
	else
		new = ft_updatemoretk(new, test, i, tools);
	if (space == 1)
	{
		txuru = ft_strjoin(" ", new);
		return (free(new), txuru);
	}
	return (new);
}

void	ft_finaltoken(char *test, unsigned int *result)
{
	char	*aux;

	aux = test;
	*result = 0;
	while (*aux != '\0' && *aux != '|' && *aux != '<' && *aux != '>')
	{
		if (*aux == '"' || *aux == '\'')
			ft_updtfinaltk(&aux, result);
		else if (*aux != ' ' && (*(aux + 1) == ' ' || *(aux + 1) == '\0'
				|| *(aux + 1) == '"' || *(aux + 1) == '\''))
			(*result)++;
		if (*aux != '\0')
			aux++;
	}
	if (*aux != '\0')
		(*result)--;
	aux--;
	if ((*aux == '"' || *aux == '\'') && *result <= 1)
		*result = 0;
}

void	ft_updatepdll(char *str, char c, unsigned int *i, unsigned int *flag)
{
	while (str[*i] == c)
		(*i)++;
	while (str[*i] != '"' && str[*i] != 92 && str[*i] != '|' && str[*i]
		&& str[*i] != '<' && str[*i] != '>' && str[*i] != 39
		&& str[*i] && str[*i] != ' ' && *flag == 0)
	{
		(*i)++;
	}
}
