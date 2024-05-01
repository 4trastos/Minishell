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

void	ft_printenvp(t_global global)
{
	int	i = 0;
	while (global.envp[i] != NULL)
	{
		printf("%s\n", global.envp[i]);
		i++;
	}
}

static t_global	global_complete(char **envp)
{
	static t_global	global;

	global.init = false;
	if (!global.init)
	{
		/* global.history = new_node(); */
		global.envp = envp;
		global.init = true;
		ft_printenvp(global);
    	/* global.paths = ft_findpaths(envp);
    	global.commands_paths = ft_split(tools->paths, ':'); */
	}
	return (global);
}

int main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (*envp == NULL)
		error_msg("Error: Missing environment variables");
	if (!ft_findpath(envp))
		error_msg("Error: finding PATH variable");
	if (argc > 1 || argv[1] != NULL)
		error_msg("This program does not accept arguments");
	global_complete(envp);
//	parse_shell(global, argv);
	prompt_loop(&tools);
	return (0);
}
