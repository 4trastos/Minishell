/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:43:59 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 20:02:59 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_validator_extra(char *echo, int *quotes, int *flag)
{
	int	len;

	len = 0;
	while (*echo != '\0')
	{
		if (*echo == ' ' && *flag == 0)
			*flag = 1;
		else if (*echo != ' ')
		{
			if (*flag == 1)
				ft_void(0);
			*flag = 0;
			if (*echo == '\'' || *echo == '"')
			{
				*quotes = 1;
				if (!ft_checkquote(echo, &len, *echo))
					return (*quotes);
				*quotes = 2;
				echo += len + 1;
			}
		}
		if (*echo != '\0')
			echo++;
	}
	return (*quotes);
}

void	ft_updateprtkn(char *str, unsigned int *i)
{
	while (str[*i] != 92 && str[*i] != '|' && str[*i]
		&& str[*i] != '<' && str[*i] != '>'
		&& str[*i] != '\'' && str[*i] != '"')
		(*i)++;
}

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*j;
	size_t			i;

	j = str;
	i = 0;
	while (i < n)
	{
		j[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	i = count * size;
	ptr = malloc(i);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, i);
	return (ptr);
}

char	*updatedollar(char *str, t_tools *tools)
{
	char	*update;
	int		subtract;
	int		add;

	add = 0;
	subtract = 0;
	update = str;
	ft_iterone(str, tools, &add, &subtract);
	str = update;
	update = ft_calloc(sizeof(char *), (ft_strlen(str) - subtract + add + 1));
	if (!update)
		return (NULL);
	update = ft_itertwo(update, str, tools);
	free(str);
	return (update);
}
