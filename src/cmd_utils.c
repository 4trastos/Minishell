/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 20:24:53 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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

void	get_command(t_list *tokens, t_executor *exe, t_tools *tools)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	exe->flag = 0;
	ft_get_commpart(tokens, exe, &flag, &i);
	if (exe->num_cmd == 1 && tokens->data[i]->op == OP_BUILTIN
		&& exe->outfile == 1)
	{
		tools->exit_code = terminator(tools, tokens->data[i]->str,
				tokens->data[i]->str, tokens->data[i]->blt);
		exe->flag = 1;
	}
	else
	{
		exe->cmd = get_cmd_aux(tokens, i);
		exe->fullcmd = ft_split(tokens->data[i]->str, ' ');
		ft_exec_cmd(tools, tokens, exe, i);
		free(exe->cmd);
		ft_doublefree(exe->fullcmd);
	}
}

void	ft_close_fd(t_executor *exe)
{
	if (exe->infile != 0)
		close(exe->infile);
	if (exe->outfile != 1)
		close(exe->outfile);
	if (exe->pipe_fd && exe->num_cmd != 0)
	{
		free(exe->pipe_fd);
		free(exe->pid);
	}
	exe->num_cmd = 0;
	exe->num_pipes = 0;
}
