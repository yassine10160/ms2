/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:29:39 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/06 13:09:46 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_var_start(char *var_value, int i, char **s, char *line)
{
	while (var_value && var_value[i] && (i > 0 && var_value[i - 1] != '='))
		i++;
	*s = alloc_expanded_str(line, var_value, i);
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
		s[i_s++] = var_value[i_var++];
	return (i_s);
}

int	handle_dollar(char *line, int i, int *sq, int *dq)
{
	int	save;

	save = *dq;
	if (!(*sq % 2) && line[i] && line[i] == '$'
		&& line[i + 1] && line[i + 1] == '?')
	{
		i += 2;
		return (i);
	}
	while (line[i] && line[i] != ' ' && !(*sq % 2))
	{
		is_in_quote(line[i], sq, dq);
		if (save != *dq)
			break ;
		i++;
	}
	return (i);
}

char	*expand_line_var(char *line, char *var_value, int i_var, int sq)
{
	char	*s;
	int		i_line;
	int		i_s;
	int		dq;
	int		flag;

	i_var = find_var_start(var_value, i_var, &s, line);
	if (!s)
		return (NULL);
	flag = 0;
	dq = 0;
	i_line = 0;
	i_s = 0;
	while (line && line[i_line])
	{
		is_in_quote(line[i_line], &sq, &dq);
		if (line[i_line] == '$' && !(sq % 2) && flag == 0 && flag++)
		{
			i_line = handle_dollar(line, i_line, &sq, &dq);
			i_s = copy_var(var_value, s, i_var, i_s);
		}
		else
			s[i_s++] = line[i_line++];
	}
	return (s);
}
