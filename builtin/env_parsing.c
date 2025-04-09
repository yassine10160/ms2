/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:20:53 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 13:21:45 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_new_env(t_env *env)
{
	t_env	*save;

	save = NULL;
	while (env->prev)
		env = env->prev;
	while (env && env->next)
	{
		save = env;
		if (env->line)
			free(env->line);
		env = env->next;
		if (save)
			free(save);
	}
	free(env);
	return (NULL);
}

char	*ft_strdup(char *str)
{
	char	*rtn;
	size_t	i;

	rtn = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!rtn)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = 0;
	return (rtn);
}

t_env	*add_lst(t_env *prev)
{
	t_env	*next;

	next = malloc(sizeof(t_env));
	if (!next)
		return (NULL);
	next->prev = prev;
	prev->next = next;
	next->line = NULL;
	next->next = NULL;
	return (next);
}

t_env	*env_to_struct(char **env)
{
	t_env	*new_env;
	t_env	*save;
	char	*line;
	int		i;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	save = new_env;
	new_env->prev = NULL;
	new_env->line = NULL;
	i = 0;
	while (env && env[i])
	{
		line = ft_strdup(env[i]);
		if (!line)
			return (free_new_env(save));
		new_env->line = line;
		new_env = add_lst(new_env);
		if (!new_env)
			return (free_new_env(save));
		i++;
	}
	new_env->next = NULL;
	return (save);
}
