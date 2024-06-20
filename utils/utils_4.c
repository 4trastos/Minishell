/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:18:50 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/20 09:26:44 by davgalle         ###   ########.fr       */
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
		if (arr_tokens[i + 1] == NULL)
		{
			if (executor(arr_tokens[i], tools) > 0)
				write(1, "ERROR\n", 6);
			i++;
		}
		else if ((arr_tokens[i + 1]->data[0]->op == 1
				|| arr_tokens[i + 1]->data[0]->op == 4)
			&& ft_find_out(arr_tokens[i]) == 0)
			i++;
		else
		{
			if (executor(arr_tokens[i], tools) > 0)
				write(1, "ERROR\n", 6);
			i++;
		}
	}
	list_matrix_delete(arr_tokens);
}
