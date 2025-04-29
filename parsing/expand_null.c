/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:28:57 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/29 13:37:13 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void init_expand_vars(int *sq, int *dq, char **dup, char *line)
{
	*sq = 0;
	*dq = 0;
	*dup = malloc(sizeof(char) * (ft_strlen(line) + 1));
}

static int skip_var(char *line, int i, int *sq, int *dq)
{
	int save;

	save = *dq;
	while (line[i] && line[i] != ' ' && !(*sq % 2))
	{
		is_in_quote(line[i], sq, dq);
		if (save != *dq)
			break;
		i++;
	}
	return (i);
}

char *expand_null(char *line, int flag, int i)
{
	char *dup;
	int j;
	int dq;
	int sq;

	init_expand_vars(&sq, &dq, &dup, line);
	if (!dup)
		return (NULL);
	j = 0;
	while (line && line[i])
	{
		is_in_quote(line[i], &sq, &dq);
		if (line[i] == '$' && !(sq % 2) && flag == 0)
		{
			flag++;
			i = skip_var(line, i, &sq, &dq);
		}
		else
			dup[j++] = line[i++];
	}
	dup[j] = '\0';
	return (dup);
}
