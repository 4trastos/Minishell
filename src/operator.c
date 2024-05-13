/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:58:01 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/13 15:45:53 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

void	get_op(t_string *token)
{
	if (ft_strncmp(token->str, "|", 1) == 0)
		token->op = OP_PIPE;
	else if (ft_strncmp(token->str, "<<", 2) == 0)
		token->op = OP_HERE_DOC;
	else if (ft_strncmp(token->str, ">>", 2) == 0)
		token->op = OP_OUTPUT_REDIRECT_APPEND;
	else if (ft_strncmp(token->str, "<", 1) == 0)
		token->op = OP_INPUT_REDIRECT;
	else if (ft_strncmp(token->str, ">", 1) == 0)
		token->op = OP_OUTPUT_REDIRECT;
	else
		token->op = OP_NONE;
}

bool	is_operators(t_string *token)
{
	if (ft_strncmp(token->str, "|", 1) == 0)
		return (false);
	else if (ft_strncmp(token->str, "<", 1) == 0)
		return (false);
	else if (ft_strncmp(token->str, ">", 1) == 0)
		return (false);
	else if (ft_strncmp(token->str, "<<", 2) == 0)
		return (false);
	else if (ft_strncmp(token->str, ">>", 2) == 0)
		return (false);
	else
		return (true);
}
