/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:14:56 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/10 10:17:19 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_word_minishell(char *str)
{
	int	count;
	int	i;
	int	dq;
	int	sq;

	count = 1;
	i = 0;
	sq = 0;
	dq = 0;
	while (str && str[i])
	{
		is_in_quote(str[i], &sq, &dq);
		if (str[i] == ' ' && !(sq % 2) && !(dq % 2))
		{
			count++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
			i++;
	}
	return (count);
}

int	word_len(char *str)
{
	int	i;
	int	dq;
	int	sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (str && str[i])
	{
		is_in_quote(str[i], &sq, &dq);
		if (!(sq % 2) && !(dq % 2) && str[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

char	*str_dup_minishell(char *s, int *i, int k, int j)
{
	char	*str;
	int		dq;
	int		sq;

	str = malloc(sizeof(char) * (word_len(s + *i) + 1));
	if (!str)
		return (NULL);
	dq = 0;
	sq = 0;
	while (s && s[k])
	{
		is_in_quote(s[k], &sq, &dq);
		if ((s[k] == ' ') && !(sq % 2) && !(dq % 2))
			break ;
		else if (s[k] == '$' && !is_alpha(s[k + 1]) && (!(sq % 2) && !(dq % 2)))
			k += 2;
		else if ((s[k] == '\'' && ((sq % 2) || (!(dq % 2))))
			|| (s[k] == '\"' && ((dq % 2) || (!(sq % 2)))))
			k++;
		else
			str[j++] = s[k++];
	}
	*i = k;
	str[j] = '\0';
	return (str);
}

void	(char *str, t_cmds *cmd)
{
	int		i;
	int		j;
	t_cmds	*save;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			cmd->token = str_dup_minishell(str, &i, i, 0);
			if (!cmd->token)
				return (NULL);
			j++;
		}
	}
	strs[j] = NULL;
	return (strs);
}
