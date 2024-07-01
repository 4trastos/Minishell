/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/30 13:34:02 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*get_doc_name(t_executor *exe)
{
	char	*str;
	char	*file;
	char	*id;

	id = ft_itoa(exe->here_doc_id);
	str = ft_strjoin("/tmp/.here_doc", id);
	file = ft_strjoin(str, ".tmp");
	free(id);
	free(str);
	return (file);
}

static int	here_doc_aux(char *limiter, int file)
{
	char	*buf;

	while (1)
	{
		buf = readline(">");
		if (g_signal != 100)
			return (free(buf), 1);
		if (!buf || (!ft_strncmp(limiter, buf, ft_strlen(limiter))
				&& ft_strlen(buf) == ft_strlen(limiter)))
			break ;
		buf = ft_strjoin(buf, "\n");
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	return (0);
}

int	here_doc(char *limiter, t_executor *exe)
{
	int		file;
	char	*file_name;

	g_signal = 100;
	file_name = get_doc_name(exe);
	file = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		return (-1);
	if (here_doc_aux(limiter, file) == 1)
		return (free(file_name), 1);
	close(file);
	exe->infile = open(file_name, O_RDONLY);
	if (exe->infile < 0)
	{
		free(file_name);
		return (-1);
	}
	free(file_name);
	return (0);
}
