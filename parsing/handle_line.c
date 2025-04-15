/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:34:14 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/15 17:43:57 by yassinefahf      ###   ########.fr       */
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
			return; // ft_exit(all, NULL);
		all->first = tmp;
		i++;
	}
	all->first = save;
}

void handle_line(t_all **all, char *line)
{
	t_data *tmp;

	tmp = (*all)->first;
	set_line(*all, line);
	(*all)->first = tmp;
	while (tmp)
	{
		while (tmp->cmds)
		{
			printf("totok: %s\n", tmp->cmds->token);
			tmp->cmds = tmp->cmds->next;
		}
		tmp = tmp->next;
	}
}
