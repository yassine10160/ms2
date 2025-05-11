/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:29:39 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/11 15:13:17 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_var_start(char *var_value, int i, int *j, int *k)
{
	while (var_value && var_value[i] && (i > 0 && var_value[i - 1] != '='))
		i++;
	*j = 0;
	*k = 0;
	return (i);
}

char	*alloc_expanded_str(char *line, char *var_value, int i_var)
{
	char	*s;

	s = ft_calloc(sizeof(char), (ft_strlen(line)
				+ ft_strlen(var_value + i_var) + 2));
	return (s);
}

int	copy_var(char *var_value, char *s, int i_var, int i_s)
{
	while (var_value && var_value[i_var] != '=')
		i_var++;
	if (var_value && var_value[i_var] == '=')
		i_var++;
	while (var_value && var_value[i_var])
	{
		s[i_s++] = var_value[i_var++];
	}
	return (i_s);
}

int	handle_dollar(char *line, int i, int *sq, int *dq)
{
	int	save_dq;
	int	save_sq;
	int	j;

	j = i;
	save_dq = *dq;
	save_sq = *sq;
	if (!(*sq % 2) && line[j] && line[j] == '$'
		&& line[j + 1] && line[j + 1] == '?')
	{
		j += 2;
		return (j);
	}
	while (line[j] && line[j] != ' ' && !(*sq % 2) && line[j] != '=')
	{
		if (line[j] == '\'' || line[j] == '"')
			break ;
		if (line[j] == '$' && j != i)
			break ;
		is_in_quote(line[j], sq, dq);
		if (save_dq != *dq || save_sq != *sq)
			break ;
		j++;
	}
	return (j);
}

char	*expand_line_var(char *line, char *var_value, int i_var, int sq)
{
	char	*s;
	int		i_line;
	int		i_s;
	int		dq;
	int		flag;

	i_var = find_var_start(var_value, i_var, &flag, &i_line);
	s = alloc_expanded_str(line, var_value, i_var);
	if (!s)
		return (NULL);
	dq = 0;
	i_s = 0;
	while (line && line[i_line])
	{
		is_in_quote(line[i_line], &sq, &dq);
		if (line[i_line] == '$' && !(sq % 2) && flag == 0)
		{
			i_line = handle_dollar(line, i_line, &sq, &dq);
			i_s = copy_var(var_value, s, i_var, i_s);
			flag++;
		}
		else
			s[i_s++] = line[i_line++];
	}
	return (s);
}
