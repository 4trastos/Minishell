/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/29 13:11:24 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

int	get_cmds(t_list *tokens)
{
	int	i;
	int	num_cmd;

	i = 0;
	num_cmd = 0;
	while (i < (int)tokens->size)
	{
		if (tokens->data[i]->op == OP_NONE)
			num_cmd++;
		i++;
	}
	return (num_cmd);
}

int	get_pipes(t_list *tokens)
{
	int	i;
	int	num_pipes;

	i = 0;
	num_pipes = 0;
	while (i < (int)tokens->size)
	{
		if (tokens->data[i]->op == OP_PIPE)
			num_pipes++;
		i++;
	}
	return (num_pipes * 2);
}

void	create_pipes(t_executor *exe)
{
	int	i;

	i = 0;
	while (i < exe->num_cmd - 1)
	{
		if (pipe(exe->pipe_fd + 2 * i) < 0)
			printf("error pipe\n");
		i++;
	}
}

void	ft_exec_cmd(t_executor *exe, int in, int out)
{
	exe->pid = fork();
	if (!exe->pid)
	{
		if (in)
			dup2(in, 0);
		if (out)
			dup2(out, 1);
		ft_close_pipes(exe);
		exe->rute = get_rute(exe->cmd, exe->path);
		if (!exe->rute)
			printf("no cmd\n");
		if (execve(exe->rute, exe->fullcmd, exe->env) == -1)
			printf("error\n");
	}
}

int	execute_cmd(t_list *tokens, t_executor *exe)
{
	exe->num_cmd = get_cmds(tokens);
	exe->num_pipes = get_pipes(tokens);
	exe->pipe_fd = (int *)malloc(sizeof(int) * exe->num_pipes);
	if (!exe->pipe_fd)
		return (-1);
	create_pipes(exe);
	exe->i = -1;
	while (++exe->i < exe->num_cmd)
	{
		exe->cmd = get_command(tokens, exe);
		printf("%s\n", exe->cmd);
		if (exe->i == 0)
		{
			if (exe->i == exe->num_cmd - 1)
				ft_exec_cmd(exe, exe->infile, exe->outfile);
			else
				ft_exec_cmd(exe, exe->infile, exe->pipe_fd[1]);
		}
		else if (exe->i == exe->num_cmd - 1)
			ft_exec_cmd(exe, exe->pipe_fd[2 * exe->i - 2], exe->outfile);
		else
			ft_exec_cmd(exe, exe->pipe_fd[2 * exe->i - 2], exe->pipe_fd[2 * exe->i - 1]);
		free(exe->cmd);
	}
	exe->i = -1;
	while (++exe->i < exe->num_cmd)
		waitpid(-1, NULL, 0);
	ft_close_fd(exe);
	return (0);
}
