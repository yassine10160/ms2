/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:27:59 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/05/19 22:23:18 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**handle_space(t_all *all, char *line, int *fd)
{
	char	**s;
	char	*buf;
	int		i;

	i = 0;
	s = split_pipe(line, "|");
	free(line);
	if (!s)
		ft_exit(all, NULL);
	while (s && s[i])
	{
		buf = add_space(s[i]);
		if (!buf)
		{
			free_strs(s);
			ft_exit(all, NULL);
		}
		*fd = check_here_doc(all, buf);
		free(s[i]);
		s[i++] = buf;
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

	tmp = all->first->cmds;
	data = all->first;
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
		else if (!is_infile(tmp->token) && !is_outfile(tmp->token))
			tmp = tmp->next;
	}
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
	// if (ft_strncmp((*all)->first->cmds->token, "./minishell", 11))
	child_handler();
	// printf("status: %d\n",(*all)->status);
	// else
		// parent_handler();
	executing(*all, 0);
}
