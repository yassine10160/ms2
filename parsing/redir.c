/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:50:23 by yafahfou          #+#    #+#             */
/*   Updated: 2025/05/18 14:25:00 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_delim(char *s, int start)
{
	int	len;
	int	sq;
	int	dq;

	len = 0;
	sq = 0;
	dq = 0;
	while (s[start] && (s[start] != ' ' || ((sq % 2) || (dq % 2))))
	{
		is_in_quote(s[start], &sq, &dq);
		if (s[start] != '\"' && s[start] != '\'')
			len++;
		start++;
	}
	return (len);
}

char	*get_delim(char *s, int index, int len)
{
	int		i;
	int		sq;
	int		dq;
	char	*delim;

	i = 0;
	sq = 0;
	dq = 0;
	delim = ft_calloc(len + 1, sizeof(char));
	if (!delim)
		return (NULL);
	while (s[index] && (s[index] != ' ' || ((sq % 2) || (dq % 2))))
	{
		is_in_quote(s[index], &sq, &dq);
		if (s[index] != '\"' && s[index] != '\'')
			delim[i++] = s[index];
		index++;
	}
	return (delim);
}

void	write_and_expand_file(t_all *all, int fd, char *line, bool is_quote)
{
	int		i;
	char	*buf;

	i = 0;
	if (!is_quote)
	{
		buf = expand_var(line, all);
		if (!buf)
		{
			free(line);
			ft_exit(all, NULL);
		}
		if (buf[ft_strlen(buf) - 1] != '\n')
			buf[ft_strlen(buf)] = '\n';
		line = buf;
	}
	while (line && line[i])
	{
		write(fd, &line[i], 1);
		i++;
	}
	free(line);
}

int	handle_here_doc(t_all *all, char *delim, bool is_quote)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		here_doc_handler();
		write(0, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (g_stop == 2)
		{
			all->status = 130;
			break ;
		}
		if (!line || ft_strncmp(line, delim, ft_strlen(delim)) == -10)
		{
			if (line)
				free(line);
			break ;
		}
		write_and_expand_file(all, fd, line, is_quote);
	}
	close(fd);
	return (fd);
}

int	check_here_doc(t_all *all, char *s)
{
	bool	is_quote;
	int		index;
	int		len;
	int		fd;
	char	*delim;

	fd = -2;
	is_quote = false;
	index = is_here_doc(s);
	if (index != -1)
	{
		all->f_here_doc = 1;
		len = len_delim(s, index);
		is_quote = is_quote_delim(s, index);
		delim = get_delim(s, index, len);
		if (!delim)
			ft_exit(all, NULL);
		fd = handle_here_doc(all, delim, is_quote);
		free(delim);
	}
	return (fd);
}
