/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/22 11:22:02 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

int	main(int argc, char **argv, char **envp)
{
	t_tools		tools;
	t_string	*cmd_input;
	char		**aux;

	cmd_input = NULL;
	if (*envp == NULL)
		error_msg("Error: Missing environment variables");
	if (!ft_findpath(envp))
		error_msg("Error: finding PATH variable");
	if (argc > 1 || argv[1] != NULL)
		error_msg("This program does not accept arguments");
	aux = dup_matrix(envp);
	tools.env = dup_matrix(ft_addshlvl(aux));
	get_pwd(&tools);
	get_old_pwd(&tools);
	while (prompt_loop(cmd_input, &tools))
		;
	return (0);
}
