/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/21 14:54:50 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	ft_setexe(t_executor *executor, t_tools *tools)
{
	executor->infile = 0;
	executor->outfile = 1;
	executor->here_doc_id = 0;
	executor->env = dup_matrix(tools->env);
	executor->path = ft_split(ft_findpath(tools->env), ':');
	executor->chk_fd = 0;
	if (tools->flag == 1)
	{
		executor->outfile = open(".trash.tmp", O_CREAT
				| O_RDWR | O_TRUNC, 0644);
	}
}

static int	ft_count(t_list *t)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 1;
	while (i < t->size)
	{
		if (t->data[i]->op == OP_PIPE && (i != 0 || i != t->size - 1))
		{
			if (t->data[i - 1]->op == OP_OUTPUT_REDIRECT
				|| t->data[i - 1]->op == OP_OUTPUT_REDIRECT_APPEND)
				count++;
			else if (t->data[i + 1]->op == OP_INPUT_REDIRECT
				|| t->data[i + 1]->op == OP_HERE_DOC)
				count++;
		}
		i++;
	}
	return (count);
}

t_list	**ft_split_tokens(t_list *tokens)
{
	t_list			**new;
	int				i;
	unsigned int	j;

	new = (t_list **)malloc(sizeof(t_list *) * ft_count(tokens) + 8);
	i = 0;
	j = 0;
	while (i < ft_count(tokens))
	{
		new[i] = new_list();
		while (j < tokens->size)
		{
			if (tokens->data[j]->op == OP_PIPE
				&& (j != 0 || j != tokens->size - 1))
			{
				if (ft_split_part(tokens, &j) == 1)
					break ;
			}
			new[i] = insert_in_list(new[i], tokens->data[j]);
			j++;
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	ft_find_out(t_list *l)
{
	int	i;

	i = 0;
	while (i < (int)l->size)
	{
		if (l->data[i]->op == 2 || l->data[i]->op == 5)
			return (1);
		i++;
	}
	return (0);
}
