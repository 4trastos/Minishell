/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicgonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/04/23 13:13:56 by nicgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

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