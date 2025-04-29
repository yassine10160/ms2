/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:40:42 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/29 14:15:18 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2, int index)
{
	char	*dest;
	int		i;
	size_t	len1;
	size_t	len2;
	int		j;

	len1 = ft_strlen((char *)s1);
	if (index == 0)
		len2 = ft_strlen((char *)s2);
	else
		len2 = (ft_strlen((char *)s2)) - (ft_strlen((char *)s2) - index);
	i = 0;
	dest = malloc((len1 + len2 + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && (size_t)j < len2)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

int	ft_index_line(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (!s || (s && s[i] == '\0'))
		return (-1);
	return (i);
}

void	ft_reset(char *s, int stop)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = s;
	if (stop == 0)
	{
		while (s && s[i])
			s[i++] = '\0';
	}
	while (tmp[stop])
	{
		s[i] = tmp[stop];
		i++;
		stop++;
	}
	while (s && s[i])
		s[i++] = '\0';
}
