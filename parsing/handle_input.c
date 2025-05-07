/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:58:44 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/07 15:06:20 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_error(char *line, char *s, t_all *all, int status)
{
	if (line)
		free(line);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	all->status = status;
}

int	parse_err(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	parse_error(char *s, t_all *all)
{
	int	i;
	int	sq;
	int	dq;

	i = -1;
	sq = 0;
	dq = 0;
	while (s && s[++i])
	{
		is_in_quote(s[i], &sq, &dq);
		if ((parse_err(s[i])) && !(sq % 2) && !(dq % 2))
		{
			if (parse_err(s[i + 1]) && s[i] == s[i + 1] && s[i] != '|')
				i++;
			i++;
			while (s[i] == ' ')
				i++;
			if ((parse_err(s[i]) && !s[i + 1]) || s[i] == '\0' || s[0] == '|')
			{
				write_error(NULL, "Error : syntax", all, 258);
				return (1);
			}
		}
	}
	return (0);
}

int	is_closed(char *line)
{
	int	i;
	int	sq;
	int	dq;

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

int	process_line(char *line, t_all *all)
{
	if (!line)
		return (0);
	if (!parse_error(line, all))
	{
		if (!is_closed(line))
			write_error(line, "Error: line not closed", all, 258);
		else
			handle_line(&all, line);
	}
	else
	{
		all->status = 2;
		free(line);
	}
	return (1);
}
