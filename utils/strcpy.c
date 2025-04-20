/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:07:47 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/20 14:56:15 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(char *line)
{
	size_t	i;

	i = 0;
	while (line && line[i])
		i++;
	return (i);
}

char	*ft_strcat(char *str_a, char *str_b, int flag, int i)
{
	char	*str;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(str_a) + ft_strlen(str_b) + 1));
	if (!str)
	{
		if (flag == 1 && str_b)
			free(str_b);
		return (NULL);
	}
	while (str_a && str_a[i])
	{
		str[i] = str_a[i];
		i++;
	}
	j = 0;
	while (str_b && str_b[j])
	{
		str[i + j] = str_b[j];
		j++;
	}
	str[i + j] = 0;
	if (flag == 1 && str_b)
		free(str_b);
	return (str);
}

char	*ft_strndup(char *str, int n)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	while (str && str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	**env_to_strs(t_env *env, int i, int count)
{
	char	**strs;

	while (env->prev)
		env = env->prev;
	while (env->next && count++)
		env = env->next;
	while (env->prev)
		env = env->prev;
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	while (env->next)
	{
		strs[i] = ft_strdup(env->line);
		if (!strs[i])
			return (free_strs(strs));
		i++;
		env = env->next;
	}
	strs[i] = ft_strdup(env->line);
	if (!strs[i])
		return (free_strs(strs));
	i++;
	strs[i] = NULL;
	return (strs);
}

char	**cmds_to_strs(t_cmds *cmds, int count, int i)
{
	char	**strs;

	while (cmds->prev)
		cmds = cmds->prev;
	while (cmds->next && count++)
		cmds = cmds->next;
	while (cmds->prev)
		cmds = cmds->prev;
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	while (cmds->next)
	{
		strs[i] = ft_strdup(cmds->token);
		if (!strs[i])
			return (free_strs(strs));
		i++;
		cmds = cmds->next;
	}
	strs[i] = NULL;
	return (strs);
}
