/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:50:23 by yafahfou          #+#    #+#             */
/*   Updated: 2025/05/03 17:10:27 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_outfile(char *s)
{
	if (s && s[0] == '>')
		return (1);
	return (0);
}

int is_here_doc(char *s)
{
	int i;
	int sq;
	int dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s && s[i])
	{
		is_in_quote(s[i], &sq, &dq);
		if (s[i] == '<' && s[i + 1] == '<' && !(sq % 2) && !(dq % 2))
		{
			i = i + 2;
			while (s[i] && s[i] == ' ')
				i++;
			return (i);
		}
		i++;
	}
	return (-1);
}

int is_append(char *s)
{
	if (s && s[0] == '>' && s[1] == '>')
		return (1);
	return (0);
}

int is_infile(char *s)
{
	if (s && s[0] == '<')
		return (1);
	return (0);
}

bool is_quote_delim(char *s, int index)
{
	int sq;
	int dq;
	bool res;

	res = false;
	sq = 0;
	dq = 0;
	while (s[index] && (s[index] != ' ' || (!(sq % 2) && !(dq % 2))))
	{
		is_in_quote(s[index], &sq, &dq);
		if ((sq % 2) || (dq % 2))
			res = true;
		index++;
	}
	if (!(sq % 2) && !(dq % 2) && res == true)
		return (true);
	return (false);
}

int len_delim(char *s, int start)
{
	int len;
	int sq;
	int dq;

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

char *get_delim(char *s, int index, int len)
{
	int i;
	int sq;
	int dq;
	char *delim;

	i = 0;
	sq = 0;
	dq = 0;
	delim = ft_calloc(len, sizeof(char));
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

void write_and_expand_file(t_all *all, int fd, char *line, bool is_quote)
{
	int i;
	char *buf;

	i = 0;
	if (!is_quote)
	{
		buf = expand_var(line, all, 0, 0);
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
}

int handle_here_doc(t_all *all, char *delim, bool is_quote)
{
	int fd;
	char *line;

	fd = open(".tmp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strcmp(line, delim))
		{
			free(line);
			break;
		}
		write_and_expand_file(all, fd, line, is_quote);
	}
	close(fd);
	fd = open(".tmp", O_RDONLY);
	return (fd);
}

int check_here_doc(t_all *all, char *s)
{
	int index;
	bool is_quote;
	int len;
	char *delim;
	int fd;

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
