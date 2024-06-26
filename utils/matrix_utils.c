/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/28 13:29:05 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	**dup_matrix(char **matrix)
{
	int		i;
	char	**dup;

	i = 0;
	if (matrix == NULL)
		return (NULL);
	while (matrix[i] != NULL)
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
	{
		dup[i] = ft_strdup(matrix[i]);
		i++;
	}
	dup[i] = NULL;
	ft_doublefree(matrix);
	return (dup);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		len;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (!s2)
	{
		free(s2);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

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
	while (mtx[len] != NULL)
		len++;
	return (len);
}
