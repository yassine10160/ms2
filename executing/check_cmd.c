/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:52:41 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/15 14:03:29 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	index_path_cmd(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;
	char	**splited_cmd;

	i = 0;
	if (!cmd || !path)
		return (-1);
	splited_cmd = split_c(cmd, ' ', '\0');
	if (!splited_cmd)
		return (-1);
	while (path[i])
	{
		path_cmd = ft_strcat(path[i], splited_cmd[0], 0, 0);
		if (!path_cmd)
			return (-1);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			free(path_cmd);
			free_strs(splited_cmd);
			return (i);
		}
		free(path_cmd);
		i++;
	}
	free_strs(splited_cmd);
	return (-1);
}

char	*get_path_cmd(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;
	char	**splited_cmd;

	if (!path || !cmd)
	{
		if (path)
			free_strs(path);
		return (NULL);
	}
	splited_cmd = split_c(cmd, ' ', '\0');
	if (!splited_cmd)
		return (free_strs(path));
	i = index_path_cmd(cmd, path);
	if (i == -1)
	{
		free_strs(splited_cmd);
		free_strs(path);
		return (NULL);
	}
	path_cmd = ft_strcat(path[i], splited_cmd[0], 0, 0);
	free_strs(splited_cmd);
	free_strs(path);
	return (path_cmd);
}