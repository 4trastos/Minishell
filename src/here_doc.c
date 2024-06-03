/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/03 13:20:18 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*get_doc_name(t_executor *exe)
{
	char	*str;

	str = ft_strjoin(".here_doc", ft_itoa(exe->here_doc_id));
	str = ft_strjoin(str, ".tmp");
	return (str);
}

int	here_doc(char *limiter, t_executor *exe)
{
	int		file;
	char	*buf;

	g_signal = 100;
	file = open(get_doc_name(exe), O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		return (-1);
	while (1)
	{
		buf = readline(">");
		if (g_signal != 100)
			return (free(buf), 1);
		if ((!ft_strncmp(limiter, buf, ft_strlen(limiter))
				&& ft_strlen(buf) == ft_strlen(limiter)) || !buf)
			break ;
		write(file, ft_strjoin(buf, "\n"), ft_strlen(buf) + 1);
		free(buf);
	}
	free(buf);
	close(file);
	exe->infile = open(get_doc_name(exe), O_RDONLY);
	if (exe->infile < 0)
		return (-1);
	return (0);
}
