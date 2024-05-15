/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/11 18:21:06 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

char	**dup_matrix(char **matrix)
{
	int		i;
	char	**dup;

	i = 0;
	while (matrix[i])
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (matrix[i])
	{
		dup[i] = ft_strdup(matrix[i]);
		i++;
	}
	return (dup);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	size_len;

	size_len = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * size_len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, size_len);
	return (ptr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = dst;
	s = src;
	i = 0;
	if (!s && !d)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_findpath(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

int	ft_mtx_len(char **mtx)
{
	int	len;

	len = 0;
	while (mtx[len])
		len++;
	return (len);
}
