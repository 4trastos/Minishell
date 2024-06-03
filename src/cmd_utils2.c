/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/11 17:36:07 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_setparams(t_list *tokens, t_executor *exe)
{
	exe->num_cmd = get_cmds(tokens);
	exe->num_pipes = get_pipes(tokens, exe);
	if (exe->num_pipes < 0)
		return (-1);
	exe->pipe_fd = (int *)malloc(sizeof(int) * exe->num_pipes);
	if (!exe->pipe_fd)
		return (-1);
	exe->pid = (pid_t *)malloc(sizeof(pid_t) * exe->num_cmd);
	if (!exe->pid)
		return (-1);
	return (0);
}

char	*get_cmd_aux(t_list *tokens, int i)
{
	int		j;
	char	*cmd;

	j = 0;
	cmd = (char *)malloc(sizeof(char) * tokens->data[i]->size + 1);
	if (!cmd)
		return (NULL);
	while (tokens->data[i]->str[j] != ' ' && tokens->data[i]->str[j] != '\0')
	{
		cmd[j] = tokens->data[i]->str[j];
		j++;
	}
	cmd[j] = '\0';
	return (cmd);
}
