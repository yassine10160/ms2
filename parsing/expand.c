/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:27:45 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/10 14:07:24 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_status(char *line, int status, int i, int j)
{
	char	*sts;
	char	*new_line;
	int		k;

	sts = ft_itoa(status);
	if (!sts)
		return (NULL);
	new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(sts)));
	if (!new_line)
	{
		free(sts);
		return (NULL);
	}
	k = 0;
	while (line && line[k])
	{
		if  (line[k] == '$' && line[k + 1] == '?')
		{
			k = k + 2;
			while (sts && sts[j])
				new_line [i++] = sts[j++];
		}
		else
			new_line[i++] = line[k++];
	}
	new_line[i] = 0;
	return (new_line);
}

static int should_expand(char *line, int i, int sq)
{
	return (line[i] == '$' && !(sq % 2) && line[i + 1] && 
		is_alpha(line[i + 1]) && 
		line[i + 1] != ' ' && line[i + 1] != '"' && 
		line[i + 1] != '\'' && !is_digit(line[i + 1]));
}

static int find_var_end(char *line, int i, int *sq, int *dq)
{
	int	j;
	int	save;

	j = i;
	save = *dq;
	while (line[j] && line[j] != ' ' && !(*sq % 2))
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
	if (ft_strcmp(var_name, "?"))
		expanded_line = expand_status(line, all->status, 0, 0);
	if (!ptr)
		expanded_line = expand_null(line, 0, 0);
	else
		expanded_line = expand_line_var(line, ptr->line, 0);
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

int main(int ac, char **av, char **env)
{
	t_all	*all;
	char	*line;

	line = ft_strdup("Salut la vie '$?' c'est' cool $?");
	all = init_all(env);
	all->first->cmds->token = line;
	expand_var(all->first->cmds->token, all, 0, 0);
	printf("%s\n", all->first->cmds->token);
}