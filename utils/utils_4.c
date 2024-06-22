/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:18:50 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/22 16:57:03 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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

int	custom_strncmp(char *prompt, char *built, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

void	ft_executator(t_list *tokens, t_tools *tools)
{
	t_list			**arr_tokens;
	unsigned int	i;

	arr_tokens = ft_split_tokens(tokens);
	i = 0;
	while (arr_tokens[i] != NULL)
	{
		tools->flag = 0;
		ft_execut_part(arr_tokens, tools, &i);
		i++;
	}
	list_matrix_delete(arr_tokens);
}

char	**dup_matrix_envp(char **matrix)
{
	int		i;
	char	**dup;

	i = 0;
	if (matrix == NULL)
		return (NULL);
	while (matrix[i] != NULL)
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
	{
		dup[i] = ft_strdup(matrix[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

int	ft_exit_toaux(char c)
{
	if (ft_isdigit(c) == 0)
	{
		write(2, "only numeric arguments allowed\n", 32);
		return (1);
	}
	return (0);
}
