/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:28:18 by dmazari           #+#    #+#             */
/*   Updated: 2025/05/19 15:49:51 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_lst_str(t_env *prev, char *var)
{
	t_env	*new_node;
	char	*dup;

	dup = ft_strdup(var);
	if (!dup)
		return (1);
	if (!prev->prev && !prev->next && !prev->line)
	{
		prev->line = dup;
		new_node = add_lst(prev);
		if (!new_node)
			return (1);
		return (0);
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->prev = prev;
	new_node->next = prev->next;
	prev->next = new_node;
	new_node->line = dup;
	return (0);
}

char	*get_var_name(char *str)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	var = malloc(sizeof(char) * (i + 2));
	if (!var)
		return (NULL);
	while (j < i)
	{
		var[j] = str[j];
		j++;
	}
	var[j] = 0;
	return (var);
}

int	modify_line(t_env *env, char *new_line)
{
	char	*save;
	char	*str;

	save = env->line;
	free(save);
	str = ft_strdup(new_line);
	if (!str)
		return (1);
	env->line = str;
	return (0);
}

int	is_valid_identifier(char *var_name, char *token)
{
	int	i;

	i = 0;
	if (!is_alpha(var_name[0]))
	{
		put_str_function("export", token, "not a  valid identifier", 2);
		return (0);
	}
	while (var_name[i])
	{
		if (!is_alphanum(var_name[i]) && var_name[i] != '_')
		{
			put_str_function("export", token, "not a  valid identifier", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
