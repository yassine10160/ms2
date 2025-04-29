/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:50:23 by yafahfou          #+#    #+#             */
/*   Updated: 2025/04/29 16:21:23 by yafahfou         ###   ########.fr       */
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
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s && s[i])
	{
		is_in_quote(s[i], &sq, &dq);
		if (s[i] == '<' && s[i + 1] == '<' && !(sq % 2) && !(dq % 2))
			return (1);
		i++;
	}
	return (0);
}

int	is_append(char *s)
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
