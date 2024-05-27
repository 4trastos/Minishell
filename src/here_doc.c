/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/26 13:30:27 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

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

	file = open(get_doc_name(exe), O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		if (get_next_line(0, &buf) < 1)
			exit(1);
		if (!ft_strncmp(limiter, buf, ft_strlen(limiter))
			&& ft_strlen(buf) -1 == ft_strlen(limiter))
			break ;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	exe->infile = open(get_doc_name(exe), O_RDONLY);
	if (exe->infile < 0)
		return (-1);
	return (0);
}
