/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:27:45 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/02 19:15:00 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	should_expand(char *line, int i, int sq)
{
	return (line[i] == '$' && !(sq % 2) && line[i + 1] && 
		(is_alpha(line[i + 1]) || (line[i + 1] == '?')) && 
		line[i + 1] != ' ' && line[i + 1] != '"' && 
		line[i + 1] != '\'' && !is_digit(line[i + 1]));
}

char	*expand_status(char *line, int status)
{
	char	*sts;
	char	*new_var;
	char	*result;
	char	*save;

	sts = ft_itoa(status);
	if (!sts)
		return (NULL);
	new_var = ft_strdup("?=");
	if (!new_var)
	{
		free(sts);
		return (NULL);
	}
	save = ft_strcat(new_var, sts, 0, 0);
	free(sts);
	free(new_var);
	if (!save)
		return (NULL);
	result = expand_line_var(line, save, 0, 0);
	free(save);
	return (result);
}

int	find_var_end(char *line, int i, int *sq, int *dq)
{
	int	j;
	int	save;

	j = i;
	save = *dq;
	while (line[j] && line[j] != ' ' && line[j] != '\n' && !(*sq % 2))
	{
		is_in_quote(line[j], sq, dq);
		if (*dq != save)
			break;
		j++;
	}
	return (j);
}

char *search_var_in_env(char *line, char *var, int end_var, t_all *all)
{
	t_env	*ptr;
	char	*var_name;
	char	*expanded_line;

	var_name = ft_strndup(var + 1, end_var);
	if (!var_name)
	{
		free(line);
		return (NULL);
	}
	ptr = find_in_env(all->env, var_name);
	if (ft_strcmp("?", var_name) == 2)
		expanded_line = expand_status(line, all->status);
	else if (!ptr)
		expanded_line = expand_null(line, 0, 0);
	else
		expanded_line = expand_line_var(line, ptr->line, 0, 0);
	free(line);
	free(var_name);
	return (expanded_line);
}

char	*expand_var(char *line, t_all *all, int i, int j)
{
	int	sq;
	int	dq;

	dq = 0;
	sq = 0;
	while (line && line[i])
	{
		is_in_quote(line[i], &sq, &dq);
		if (should_expand(line, i, sq))
		{
			j = find_var_end(line, i, &sq, &dq);
			line = search_var_in_env(line, line + i, (j - i - 1), all);
			if (!line)
				return (NULL);
		}
		i++;
	}
	return (line);
}

// int main(int ac, char **av, char **env)
// {
// 	t_all	*all;
// 	char	*line;

// 	(void)ac;
// 	(void)av;
// 	line = ft_strdup("Salut la vie $? c'est' cool $bn");
// 	all = init_all(env);
// 	all->first->cmds->token = line;
// 	all->status = 12345;
// 	line = expand_var(all->first->cmds->token, all, 0, 0);
// 	split_minishell(line, all);
// 		while (all->first->cmds->next)
// 	{
// 		printf("%s\n", all->first->cmds->token);
// 		all->first->cmds = all->first->cmds->next;
// 	}
// }