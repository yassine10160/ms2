/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:26:08 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/05 13:27:38 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export(t_env *env, int i)
{
	int	q;

	while (env->prev)
		env = env->prev;
	while (env->next)
	{
		printf("export ");
		i = 0;
		q = 0;
		while (env->line[i])
		{
			if ((i > 0) && (env->line[i - 1] == '='))
			{
				printf("\"");
				q++;
			}
			printf("%c", env->line[i]);
			i++;
		}
		if (q == 1)
			printf("\"");
		printf("\n");
		env = env->next;
	}
	return (0);
}

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

int	ft_export(t_env *env, t_cmds *cmds)
{
	char	*var_name;
	t_env	*save;
	int		i;

	i = 0;
	if (!cmds || !cmds->token)
		return (print_export(env, 0));
	var_name = get_var_name(cmds->token);
	if (!var_name)
		return (1);
	while (var_name[i] && (is_alphanum(var_name[i]) || var_name[i] == '_') && (is_alpha(var_name[0])))
		i++;
	if (var_name[i])
	{
		printf("export: '%s': not a valid identifier\n", cmds->token);
		free(var_name);
		return (2);
	}
	save = find_in_env(env, var_name);
	free(var_name);
	if (!save)
	{
		if (add_lst_str(env, cmds->token))
			return (1);
	}
	else
		if (modify_line(save, cmds->token))
			return (1);
	return (0);
}
