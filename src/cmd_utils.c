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
#include "../incl/list.h"
#include "../incl/executor.h"

static int	get_rute_aux(char *comand)
{
	int	i;

	i = 0;
	while (comand[i] != '\0')
	{
		if (comand[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*get_rute(char *comand, char **paths)
{
	char	*tmp;
	char	*exe;

	if (get_rute_aux(comand) == 1)
		return (comand);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		exe = ft_strjoin(tmp, comand);
		free(tmp);
		if (access(exe, 0) == 0)
			return (exe);
		free(exe);
		paths++;
	}
	return (comand);
}

void	ft_close_pipes(t_executor *exe)
{
	int	i;

	i = 0;
	while (i < (exe->num_pipes))
	{
		close(exe->pipe_fd[i]);
		i++;
	}
}

char	*get_command(t_list *tokens, t_executor *exe)
{
	int 	i;
	int 	j;
	int 	flag;
	char	*cmd;

	i = 0;
	flag = 0;
	j = 0;
	cmd = NULL;
	while (tokens->data[i] != NULL)
	{
		if (tokens->data[i]->op == OP_NONE)
		{
			if (flag == exe->i)
				break;
			flag++;
		}
		i++;
	}
	cmd = (char *)malloc(sizeof(char) * tokens->data[i]->size + 1);
	while (tokens->data[i]->str[j] != ' ' && tokens->data[i]->str[j] != '\0')
	{
		cmd[j] = tokens->data[i]->str[j];
		j++;
	}
	cmd[j] = '\0';
	exe->fullcmd = ft_split(tokens->data[i]->str, ' ');
	return(cmd);
}

void	ft_close_fd(t_executor *exe)
{
	if (exe->infile != 0)
		close(exe->infile);
	if (exe->outfile != 1)
		close(exe->outfile);
}
