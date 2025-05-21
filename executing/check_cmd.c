/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 00:38:11 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/21 13:13:10 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

int	check_path(char *path_i, char *cmd, char **path_cmd)
{
	struct stat	statbuf;

	*path_cmd = ft_strcat(path_i, cmd, 0, 0);
	if (!*path_cmd)
		return (-1);
	if (access(*path_cmd, F_OK) == 0)
	{
		if (lstat(*path_cmd, &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
			{
				free(*path_cmd);
				return (0);
			}
			if (access(*path_cmd, X_OK) == 0)
				return (1);
		}
	}
	free(*path_cmd);
	return (0);
}

static char	*handle_direct_cmd(char *cmd, t_all *all)
{
	struct stat	statbuf;

	if (access(cmd, F_OK) != 0)
	{
		put_str_error(cmd, "No such file or directory", 2);
		all->status = 127;
		return (NULL);
	}
	if (lstat(cmd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		put_str_error(cmd, "Is a directory", 2);
		all->status = 126;
		return (NULL);
	}
	if (access(cmd, X_OK) != 0)
	{
		put_str_error(cmd, "Permission denied", 2);
		all->status = 126;
		return (NULL);
	}
	return (ft_strdup(cmd));
}

char	*get_path_cmd(char *cmd, char **path, t_all *all, int i)
{
	char	*path_cmd;
	int		result;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_direct_cmd(cmd, all));
	if (!path)
	{
		put_str_error(cmd, "command not found", 2);
		all->status = 127;
		return (NULL);
	}
	i = -1;
	while (path[++i])
	{
		result = check_path(path[i], cmd, &path_cmd);
		if (result == 1)
			return (path_cmd);
		else if (result == -1)
			return (NULL);
	}
	put_str_error(cmd, "command not found", 2);
	all->status = 127;
	return (NULL);
}
