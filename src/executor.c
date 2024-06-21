/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/18 10:55:13 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	ft_empty_doc(t_executor *exe, t_tools *tools)
{
	int	fd;

	fd = open(".empty", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close(fd);
	exe->infile = open(".empty", O_RDONLY);
	if (tools->exit_code == 130)
		exe->chk_fd = 2;
	else
		exe->chk_fd = 1;
}

void	delete_heredoc(t_executor *exe)
{
	char	*file;

	while (exe->here_doc_id >= 0)
	{
		file = get_doc_name(exe);
		unlink(file);
		free(file);
		exe->here_doc_id--;
	}
	unlink(".trash.tmp");
	unlink(".empty");
	ft_doublefree(exe->env);
	ft_doublefree(exe->path);
}

int	get_infile(t_string *infile, t_executor *exe, t_tools *tools)
{
	int	status;

	if (infile->op == OP_INPUT_REDIRECT)
	{
		exe->infile = open(ft_strtrim(infile->str, "<"), O_RDONLY);
		if (exe->infile < 0)
		{
			perror("file");
			ft_empty_doc(exe, tools);
		}
	}
	else
	{
		status = here_doc(ft_strtrim(infile->str, "<"), exe);
		if (status < 0)
			unlink(get_doc_name(exe));
		else if (status == 1)
		{
			unlink(get_doc_name(exe));
			tools->exit_code = 130;
			ft_empty_doc(exe, tools);
		}
		exe->here_doc_id++;
	}
	return (1);
}

int	get_outfile(t_string *outfile, t_executor *exe)
{
	outfile->str = ft_strtrim(outfile->str, ">");
	if (outfile->op == OP_OUTPUT_REDIRECT)
	{
		exe->outfile = open(outfile->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (exe->outfile < 0)
			exe->outfile = 1;
	}
	else
	{
		exe->outfile = open(outfile->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (exe->outfile < 0)
			exe->outfile = 1;
	}
	return (0);
}

int	executor(t_list *tokens, t_tools *tools)
{
	unsigned int	i;
	t_executor		executor;

	ft_setexe(&executor, tools);
	i = 0;
	while (i < tokens->size)
	{
		if (tokens->data[i]->op == OP_INPUT_REDIRECT
			|| tokens->data[i]->op == OP_HERE_DOC)
		{
			if (get_infile(tokens->data[i], &executor, tools) < 0)
				return (1);
		}
		else if (tokens->data[i]->op == OP_OUTPUT_REDIRECT
			|| tokens->data[i]->op == OP_OUTPUT_REDIRECT_APPEND)
		{
			if (get_outfile(tokens->data[i], &executor) < 0)
				return (1);
		}
		i++;
	}
	if (execute_cmd(tokens, &executor, tools) < 0)
		return (1);
	delete_heredoc(&executor);
	return (0);
}
