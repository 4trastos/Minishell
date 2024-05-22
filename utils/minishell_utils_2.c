/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/20 20:21:13 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

static char	*ft_sticky(char const *s1, char const *s2, char *cadena)
{
	int	j;
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		cadena[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		cadena[i] = s2[j];
		i++;
		j++;
	}
	cadena[i] = '\0';
	return (cadena);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*cadena;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	cadena = (char *)malloc(len1 + len2 + 1);
	if (cadena == NULL)
		return (NULL);
	cadena = ft_sticky(s1, s2, cadena);
	return (cadena);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_substrop(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*sub;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{
		while (s[start] == ' ')
			start++;
		sub[j] = s[start];
		j++;
		start++;
	}
	sub[j] = '\0';
	return (sub);
}

int	ft_echocmp(char *str, char *dst)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	write(1, "Dentro de echocmp\n", 18);
	while (str[i] == dst[i] && dst[i] != '\0')
		i++;
	if (str[i] != dst[i])
	{
		write(1, "Diferente\n", 10);
		return (1);
	}
	return (0);
}
