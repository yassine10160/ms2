/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:52:41 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/20 14:57:40 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	index_path_cmd(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	if (!cmd || !path)
		return (-1);
	while (path[i])
	{
		path_cmd = ft_strcat(path[i], cmd, 0, 0);
		if (!path_cmd)
			return (-1);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			free(path_cmd);
			return (i);
		}
		free(path_cmd);
		i++;
	}
	return (-1);
}

char	*get_path_cmd(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	if (!path || !cmd)
	{
		if (path)
			free_strs(path);
		return (NULL);
	}
	i = index_path_cmd(cmd, path);
	if (i == -1)
	{
		free_strs(path);
		printf("%s : command not found\n", cmd);
		return (NULL);
	}
	path_cmd = ft_strcat(path[i], cmd, 0, 0);
	free_strs(path);
	return (path_cmd);
}
