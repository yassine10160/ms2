/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:27:59 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/05/21 17:52:39 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_pipe_segment(t_all *all, char ***s, int i, int *fd)
{
	char	*buf;
	int		index;

	index = 0;
	buf = add_space((*s)[i]);
	if (!buf)
		return (-1);
	*fd = check_here_doc(all, buf, &index);
	while (*fd > 0 && buf[index] && is_here_doc(buf, index) != -1)
	{
		close(*fd);
		*fd = check_here_doc(all, buf, &index);
	}
	free((*s)[i]);
	(*s)[i] = buf;
	return (0);
}

char	**handle_space(t_all *all, char *line, int *fd)
{
	char	**s;
	int		i;

	i = 0;
	s = split_pipe(line, "|");
	free(line);
	if (!s)
		ft_exit(all, NULL);
	while (s && s[i])
	{
		if (process_pipe_segment(all, &s, i, fd) == -1)
		{
			free_strs(s);
			ft_exit(all, NULL);
		}
		i++;
	}
	return (s);
}

int	set_line(t_all *all, char *line, int i, int fd)
{
	char	**s;
	t_data	*save;
	t_data	*tmp;

	s = handle_space(all, line, &fd);
	i = process_lines(s, all, i);
	i = 0;
	save = all->first;
	while (s && s[i])
	{
		split_quote_and_space(s[i], all);
		if (s[i + 1])
		{
			tmp = add_next_data(all->first);
			all->first = tmp;
			if (!tmp)
				ft_exit(all, NULL);
		}
		i++;
	}
	free_strs(s);
	all->first = save;
	return (fd);
}

void	handle_all(t_all *all, int fd)
{
	t_cmds	*tmp;
	t_data	*data;
	t_data	*save;

	tmp = all->first->cmds;
	data = all->first;
	save = all->first;
	while (tmp && data)
	{
		handle_redirection(&tmp, data, fd);
		if (!tmp || !tmp->next)
		{
			if (data->next)
				data = data->next;
			else
				break ;
			tmp = data->cmds;
		}
		else if ((!is_infile(tmp->token) && !is_outfile(tmp->token))
			|| tmp->is_quote_redir)
			tmp = tmp->next;
	}
	all->first = save;
}

void	handle_line(t_all **all, char *line)
{
	t_data	*tmp;
	int		fd;

	fd = -2;
	tmp = (*all)->first;
	fd = set_line(*all, line, 0, -2);
	(*all)->first = tmp;
	handle_all(*all, fd);
	tmp = (*all)->first;
	child_handler(1);
	executing(*all, 0);
}
