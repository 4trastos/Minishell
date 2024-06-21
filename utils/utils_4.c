/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:18:50 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/21 15:01:43 by davgalle         ###   ########.fr       */
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
