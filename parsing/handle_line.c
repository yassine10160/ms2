/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:27:59 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/26 15:29:05 by yassinefahf      ###   ########.fr       */
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
		tmp = add_next_data(all->first);
		if (!tmp)
			ft_exit(all, NULL);
		all->first = tmp;
		i++;
	}
	free_strs(s);
	all->first = save;
}

int is_infile(char *s)
{
	if (s && s[0] == '<')
		return (1);
	return (0);
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
	else
	{
		data->fd_out = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (data->fd_out == -1)
			ft_exit(all, NULL);
	}
}

int is_outfile(char *s)
{
	if (s && s[0] == '>')
		return (1);
	return (0);
}
int is_here_doc(char *s)
{
	if (s && s[0] == '<' && s[1] == '<')
		return (1);
	return (0);
}

int handle_here_doc(t_all *all, t_cmds *cmd)
{
	if (cmd || all)
		return (0);
	else
		return (1);
}

t_cmds *handle_all(t_all *all)
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
		}
		else if (is_outfile(tmp->token))
		{
			safe_open(all, data, tmp->next->token, OUTFILE);
			tmp = remove_cmd(tmp);
			tmp = remove_cmd(tmp);
			// printf("my node: %s\n", tmp->next);
		}
		else if (is_here_doc(tmp->token))
		{
			handle_here_doc(all, tmp);
			remove_cmd(tmp->next);
			remove_cmd(tmp);
		}
		if (!tmp->next->next)
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
	return (tmp);
}

void handle_line(t_all **all, char *line)
{
	t_data *tmp;
	t_cmds *cmd;

	tmp = (*all)->first;
	set_line(*all, line);
	(*all)->first = tmp;
	cmd = handle_all(*all);
	// printf("new cmd %s\n", cmd->token);
	tmp->cmds = cmd;
	// tmp = (*all)->first;
	// printf("here\n");
	while (tmp->next)
	{
		while (tmp->cmds)
		{
			printf("totok: %s\n", tmp->cmds->token);
			tmp->cmds = tmp->cmds->next;
		}
		printf("fdin: %d\n", tmp->fd_in);
		printf("fdout: %d\n", tmp->fd_out);
		tmp = tmp->next;
	}
}
