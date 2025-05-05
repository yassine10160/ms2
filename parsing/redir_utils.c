/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:38:45 by dmazari           #+#    #+#             */
/*   Updated: 2025/05/05 14:39:01 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_outfile(char *s)
{
	if (s && s[0] == '>')
		return (1);
	return (0);
}

int	is_here_doc(char *s)
{
	int	i;
	int	sq;
	int	dq;

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

int	is_append(char *s)
{
	if (s && s[0] == '>' && s[1] == '>')
		return (1);
	return (0);
}

int	is_infile(char *s)
{
	if (s && s[0] == '<')
		return (1);
	return (0);
}

bool	is_quote_delim(char *s, int index)
{
	int		sq;
	int		dq;
	bool	res;

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
