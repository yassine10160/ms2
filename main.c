/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:08:05 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/18 14:45:47 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void new_line(t_all *all)
{
	free_data(all->first);
	all->first = init_data();
	if (!all->first)
		ft_exit(all, NULL);
}

void exit_parse(char *s, t_all *all, int status)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	all->status = status;
	// il faut free la struct all
}

int is_parse_err(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int parse_error(char *str, t_all *all)
{
	int i;
	int sq;
	int dq;

	i = -1;
	sq = 0;
	dq = 0;
	while (str && str[++i])
	{
		is_in_quote(str[i], &sq, &dq);
		if ((is_parse_err(str[i])) && !(sq % 2) && !(dq % 2))
		{
			if (is_parse_err(str[i + 1]) && str[i] == str[i + 1] && str[i] != '|')
				i++;
			i++;
			while (str[i] == ' ')
				i++;
			if ((is_parse_err(str[i]) || str[i] == '\0'))
			{
				exit_parse("parsing error\n", all, 258);
				return (1);
			}
		}
	}
	return (0);
}

int is_closed(char *line)
{
	int i;
	int sq;
	int dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (line && line[i])
	{
		is_in_quote(line[i], &sq, &dq);
		i++;
	}
	if ((dq % 2) || (sq % 2))
		return (0);
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_all *all;
	char *line;

	(void)ac;
	(void)av;
	all = init_all(env);
	while (1)
	{
		line = readline(NULL);
		if (line)
		{
			if (!parse_error(line, all))
			{
				if (!is_closed(line))
					exit_parse("error: line not closed", all, 258);
				else
					handle_line(&all, line);
			}
			else
				ft_exit(all, NULL);
		}
		else
			ft_exit(all, NULL);
	}
}
