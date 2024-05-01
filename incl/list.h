/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/01 09:31:10 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIST_H
# define LIST_H

# include "../incl/minishell.h"

typedef struct s_list
{
    unsigned int    size;
    char           *data;
}   t_list;

/*** LIST & NODES ***/

t_list  *new_node(void);

#endif