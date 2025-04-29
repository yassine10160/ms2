/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:27:59 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/29 13:21:55 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **handle_space(t_all *all, char *line)
{
	char **s;
	int i;
	char *buf;

	i = 0;
	s = split_pipe(line, "|");
	free(line);
	if (!s)
		return NULL; // ft_exit(all, NULL)
	while (s && s[i])
	{
		buf = add_space(s[i]);
		if (!buf)
		{
			free_strs(s);
			free_all(all);
			// ft_exit(all, NULL)
		}
		free(s[i]);
		s[i++] = buf;
	}
	return (s);
}

void set_line(t_all *all, char *line)
{
	char **s;
	int i;
	char *buf;
	t_data *save;
	t_data *tmp;

	i = 0;
	s = handle_space(all, line);
	while (s && s[i])
	{
		buf = expand_var(s[i], all, 0, 0);
		if (!buf)
		{
			free_strs(s);
			return; // ft_exit(all, NULL)
		}
		s[i++] = buf;
	}
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
}

void safe_open(t_all *all, t_data *data, char *file, int type)
{
	if (type == INFILE)
	{
		data->fd_in = open(file, O_RDONLY);
		if (data->fd_in == -1)
			printf("no such file\n");
		// ft_exit(all, NULL);
	}
	else if (type == OUTFILE)
	{
		data->fd_out = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (data->fd_out == -1)
			ft_exit(all, NULL);
	}
	else
	{
		data->fd_out = open(file, O_WRONLY | O_CREAT, 0777);
		if (data->fd_out == -1)
			ft_exit(all, NULL);
	}
}

int handle_here_doc(t_all *all, t_cmds *cmd)
{
	all->f_here_doc = open(".tmp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (all->f_here_doc == -1)
		ft_exit(all, NULL);
	check_delim()
	

}

void	handle_all(t_all *all)
{
	t_cmds *tmp;
	t_data *data;

	tmp = all->first->cmds;
	data = all->first;
	while (tmp && data)
	{
		if (is_infile(tmp->token))
		{
			safe_open(all, data, tmp->next->token, INFILE);
			tmp = remove_cmd(tmp);
			tmp = remove_cmd(tmp);
			data->cmds = tmp;
		}
		else if (is_outfile(tmp->token))
		{
			if (is_append(tmp->token))
				safe_open(all, data, tmp->next->token, APPEND);
			else
				safe_open(all, data, tmp->next->token, OUTFILE);
			tmp = remove_cmd(tmp);
			tmp = remove_cmd(tmp);
			data->cmds = tmp;
		}
		else if (is_here_doc(tmp->token))
		{
			handle_here_doc(all, tmp);
			remove_cmd(tmp->next);
			remove_cmd(tmp);
		}
		if (!tmp->next || !tmp->next->next)
		{
			if (data->next->next)
				data = data->next;
			else
				break;
			tmp = data->cmds;
		}
		else
			tmp = tmp->next;
	}
}

void handle_line(t_all **all, char *line)
{
	t_data *tmp;
	// t_cmds *cmd;

	tmp = (*all)->first;
	set_line(*all, line);
	(*all)->first = tmp;
	handle_all(*all);
	tmp = (*all)->first;
	// printf("tmp %s\n", tmp->cmds->token);
	while (tmp->next)
	{
		while (tmp->cmds)
		{
			if (tmp->cmds && tmp->cmds->token)
				printf("totok: %s\n", tmp->cmds->token);
			tmp->cmds = tmp->cmds->next;
		}
		printf("fdin: %d\n", tmp->fd_in);
		printf("fdout: %d\n", tmp->fd_out);
		tmp = tmp->next;
	}
}
