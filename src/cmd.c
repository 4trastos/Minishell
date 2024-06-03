/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/03 13:21:18 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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

int	get_pipes(t_list *tokens, t_executor *exe)
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
	if ((num_pipes) > exe->num_cmd)
		return (-1);
	return (num_pipes * 2);
}

void	create_pipes(t_executor *exe)
{
	int	i;

	i = 0;
	while (i < exe->num_cmd -1)
	{
		if (pipe(exe->pipe_fd + 2 * i) < 0)
			printf("error pipe\n");
		i++;
	}
}

void	ft_exec_cmd(t_executor *exe)
{
	exe->pid[exe->i] = fork();
	if (!exe->pid[exe->i])
	{
		if (exe->i == 0)
		{
			if (exe->i == exe->num_cmd - 1)
				ft_dup2(exe->infile, exe->outfile);
			else
				ft_dup2(exe->infile, exe->pipe_fd[1]);
		}
		else if (exe->i == exe->num_cmd - 1)
			ft_dup2(exe->pipe_fd[2 * exe->i - 2], exe->outfile);
		else
			ft_dup2(exe->pipe_fd[2 * exe->i - 2], exe->pipe_fd[2 * exe->i + 1]);
		ft_close_pipes(exe);
		exe->rute = get_rute(exe->cmd, exe->path);
		if (!exe->rute)
			perror("comand");
		exe->exit_code = execve(exe->rute, exe->fullcmd, exe->env);
		if (exe->exit_code == -1)
			perror("excve");
		exit(exe->exit_code);
	}
}

int	execute_cmd(t_list *tokens, t_executor *exe)
{
	if (ft_setparams(tokens, exe) == -1)
		return (-1);
	create_pipes(exe);
	exe->i = -1;
	while (++exe->i < exe->num_cmd)
	{
		exe->cmd = get_command(tokens, exe);
		ft_exec_cmd(exe);
		free(exe->cmd);
	}
	exe->i = -1;
	ft_close_pipes(exe);
	while (++exe->i < exe->num_cmd)
		waitpid(exe->pid[exe->i], &exe->status, 0);
	if (WIFEXITED(exe->status))
		exe->exit_code = WEXITSTATUS(exe->status);
	ft_close_fd(exe);
	return (0);
}
