/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/04/30 18:24:03 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

static t_global	global_complete(char **envp, t_tools *tools)
{
	static t_global	global;

	global.init = false;
	if (!global.init)
	{
		global.envp = envp;
		global.init = true;
	}
	tools->ptr_global = &global;
	return (global);
}

int main(int argc, char **argv, char **envp)
{
	t_tools		tools;
	t_string	*cmd_input;

	cmd_input = NULL;
	if (*envp == NULL)
		error_msg("Error: Missing environment variables");
	if (!ft_findpath(envp))
		error_msg("Error: finding PATH variable");
	if (argc > 1 || argv[1] != NULL)
		error_msg("This program does not accept arguments");	
	global_complete(envp, &tools);
	while (prompt_loop(cmd_input))
		;
	return (0);
}
