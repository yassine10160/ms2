/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:26:08 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/03 16:59:05 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int print_export(t_env *env, int i)
{
	int q;

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

int add_lst_str(t_env *prev, char *var)
{
	t_env *new_node;
	// t_env	*ptr;
	char *dup;

	dup = ft_strdup(var);
	// if (!dup)
	// 	ft_exit(all);
	if (!prev->prev && !prev->next && !prev->line)
	{
		prev->line = dup;
		// ptr = add_lst(prev);
		// if (!ptr)
		// 	ft_exit(all);
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

char *get_var_name(char *str)
{
	char *var;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	var = malloc(sizeof(char) * (i + 2));
	if (!var)
		return (NULL);
	while (j <= i)
	{
		var[j] = str[j];
		j++;
	}
	var[j] = 0;
	return (var);
}

void modify_line(t_env *env, char *new_line)
{
	char *save;
	char *str;

	save = env->line;
	free(save);
	str = ft_strdup(new_line);
	// if (!str)
	// ft_exit(all);
	env->line = str;
}

int ft_export(t_env *env, t_cmds *cmds)
{
	char *var_name;
	t_env *save;

	if (!cmds || !cmds->token)
		return (print_export(env, 0));
	var_name = get_var_name(cmds->token);
	if (!var_name)
		return (1);
	if (is_alpha(var_name[0]) != 1)
	{
		printf("export: '%s': not a valid identifier\n", var_name);
		free(var_name);
		return (2);
	}
	save = find_in_env(env, var_name);
	free(var_name);
	if (!save)
	{
		if (add_lst_str(env, cmds->token) == 1)
			return (1);
	}
	else
		modify_line(save, cmds->token);
	return (0);
}
