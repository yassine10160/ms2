/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:52:41 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/22 14:19:19 by dmazari          ###   ########.fr       */
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

void	check_local(char *cmd, char **path_cmd)
{
	char	*pwd;

	pwd = get_pwd(NULL);
	if (!pwd)
	{
		*path_cmd = NULL;
		return ;
	}
	*path_cmd = ft_strcat(ft_strcat(pwd, "/", 0, 0), cmd, 0, 0);
	free(pwd);
	if (!*path_cmd)
		return ;
	if (access(*path_cmd, F_OK | X_OK) == 0)
		return ;
	free(*path_cmd);
	*path_cmd = NULL;
	return ;
}

char	*get_path_cmd(char *cmd, char **path, t_all *all)
{
	int		i;
	char	*path_cmd;

	if (!path || !cmd)
	{
		if (path)
			free_strs(path);
		return (NULL);
	}
	check_local(cmd, &path_cmd);
	if (path_cmd)
	{
		free_strs(path);
		return (path_cmd);
	}
	i = index_path_cmd(cmd, path);
	if (i == -1)
	{
		free_strs(path);
		all->status = 127;
		printf("%s : command not found\n", cmd);
		return (NULL);
	}
	path_cmd = ft_strcat(path[i], cmd, 0, 0);
	free_strs(path);
	return (path_cmd);
}
