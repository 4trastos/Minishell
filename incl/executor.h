/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/11 17:36:07 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../incl/minishell.h"
# include "../incl/list.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_executor
{
	int	here_doc_id;
	int	infile;
	int	outfile;
}	t_executor;


int		here_doc(char *limiter, t_executor *exe);
int		get_infile(t_string *infile, t_executor *exe);
int		executor(t_list *tokens);
int		get_outfile(t_string *outfile, t_executor *exe);
char	*ft_new_line(char *board);
char	*ft_line(char *board);
char	*ft_read(int fd, char *board, int	*bytes_read);
int		get_next_line(int fd, char **line);
char	*get_doc_name(t_executor *exe);


#endif