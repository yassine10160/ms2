/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:55:06 by yafahfou          #+#    #+#             */
/*   Updated: 2025/05/13 13:50:17 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*sa_gnl(int fd)
{
	write(fd, "\n", 1);
	put_str_error("warning", "here_document delimited by ctrl_D", fd);
	return (NULL);
}

char	*ft_strjoin_check(char *s1, char *s2)
{
	char	*tmp;
	int		index_line;

	index_line = ft_index_line(s2);
	tmp = ft_strjoin_gnl(s1, s2, index_line + 1);
	if (s1)
		free(s1);
	return (tmp);
}

int	read_file(char *buff, char **str, int fd)
{
	ssize_t	bytes;

	bytes = -2;
	if (buff[0])
	{
		*str = ft_strjoin_check(*str, buff);
		if (!*str)
			return (-1);
		ft_reset(buff, ft_index_line(buff) + 1);
	}
	while (ft_index_line(*str) < 0 && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == 0)
			return (0);
		if (bytes > 0)
			buff[bytes] = '\0';
		*str = ft_strjoin_check(*str, buff);
		if (!*str || bytes == -1 || buff[0] == '\0')
			return (free(*str), -1);
		ft_reset(buff, ft_index_line(buff) + 1);
	}
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*str;
	ssize_t		bytes;

	bytes = -2;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (buff[0] = '\0', NULL);
	str = NULL;
	bytes = read_file(buff, &str, fd);
	if (bytes == -1)
	{
		ft_reset(buff, ft_index_line(buff) + 1);
		return (NULL);
	}
	else if (bytes == 0)
		return (sa_gnl(fd));
	if (ft_index_line(buff) != -1 && bytes == -2 && ft_index_line(str) == -1)
	{
		str = ft_strjoin_check(str, buff);
		if (!str)
			return (NULL);
	}
	return (str);
}
