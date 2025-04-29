/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:50:23 by yafahfou          #+#    #+#             */
/*   Updated: 2025/04/29 11:51:46 by yafahfou         ###   ########.fr       */
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
	if (s && s[0] == '<' && s[1] == '<')
		return (1);
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
