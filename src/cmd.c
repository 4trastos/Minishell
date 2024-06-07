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

int	get_cmds(t_list *tokens, t_executor *exe)
{
	int	i;
	int	num_cmd;

	i = 0;
	num_cmd = 0;
	while (i < (int)tokens->size)
	{
		if (tokens->data[i]->op == OP_NONE || tokens->data[i]->op == OP_BUILTIN
			|| tokens->data[i]->op == OP_DOLLAR_SIGN)
			num_cmd++;
		if (tokens->data[i]->op == OP_BUILTIN)
			exe->num_built++;
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

void	ft_exec_cmd(t_tools *tools, t_list *tokens, t_executor *exe, int i)
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
		if (tokens->data[i]->op == OP_BUILTIN)
		{
			terminator(tools, tools->prompt, tokens->data[i]->str, tokens->data[i]->blt);
			exe->exit_code = 0;
		}
		else if (tokens->data[i]->op == OP_NONE)
		{
			exe->rute = get_rute(exe->cmd, exe->path);
			if (!exe->rute)
				perror("comand");
			exe->exit_code = execve(exe->rute, exe->fullcmd, tools->env);
			if (exe->exit_code == -1)
				perror("excve");
		}
		else if (tokens->data[i]->op == OP_DOLLAR_SIGN)
		{
			ft_hatedollar(tokens->data[i]->str, tools->env);
			printf("\n");
		}
		exit(exe->exit_code);
	}
}

int	execute_cmd(t_list *tokens, t_executor *exe, t_tools *tools)
{
	if (ft_setparams(tokens, exe) == -1)
		return (-1);
	create_pipes(exe);
	exe->i = -1;
	while (++exe->i < exe->num_cmd)
		get_command(tokens, exe, tools);
	exe->i = -1;
	ft_close_pipes(exe);
	while (++exe->i < exe->num_cmd)
		waitpid(-1, &exe->status, 0);
	if (WIFEXITED(exe->status))
		exe->exit_code = WEXITSTATUS(exe->status);
	ft_close_fd(exe);
	return (0);
}
