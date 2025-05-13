/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:52:41 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/13 19:10:31 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_file_permission(char *cmd, char *path_cmd, t_all *all)
{
	struct stat	statbuf;

	if (lstat(path_cmd, &statbuf) == 0)
	{
		if (S_ISREG(statbuf.st_mode))
		{
			if (statbuf.st_mode & S_IXUSR)
				return (path_cmd);
			else
				return (handle_exec_error(cmd, path_cmd, all, 0));
		}
		else
			return (handle_exec_error(cmd, path_cmd, all, 1));
	}
	free(path_cmd);
	return (NULL);
}

char	*handle_not_found(char *cmd, char **path, t_all *all)
{
	if (path)
		free_strs(path);
	if (ft_strcmp(cmd, "./") == 1)
		put_str_error(cmd, "No such file or directory", 2);
	else
		put_str_error(cmd, "command not found", 2);
	all->status = 127;
	return (NULL);
}

int	index_path_cmd(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	if (!cmd || !path)
		return (-1);
	if (ft_strcmp(cmd, "./") == 1)
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

int	check_local(char *cmd, char **path_cmd)
{
	char	*pwd;
	char	*tmp;

	pwd = get_pwd(NULL);
	if (!pwd)
	{
		*path_cmd = NULL;
		return (0);
	}
	tmp = ft_strcat(pwd, "/", 0, 0);
	free(pwd);
	if (!tmp)
		return (0);
	*path_cmd = ft_strcat(tmp, cmd, 0, 0);
	free(tmp);
	if (!*path_cmd)
		return (0);
	if (access(*path_cmd, F_OK) == 0)
		return (1);
	free(*path_cmd);
	*path_cmd = NULL;
	return (0);
}

char	*get_path_cmd(char *cmd, char **path, t_all *all)
{
	int		i;
	char	*path_cmd;

	path_cmd = NULL;
	if (!cmd)
		return (NULL);
	if (check_local(cmd, &path_cmd))
		return (check_file_permission(cmd, path_cmd, all));
	if (path_cmd)
		free(path_cmd);
	if (!path)
	{
		put_str_fd("Error: PATH not defined\n", 2);
		all->status = 127;
		return (NULL);
	}
	i = index_path_cmd(cmd, path);
	if (i == -1)
		return (handle_not_found(cmd, path, all));
	path_cmd = ft_strcat(path[i], cmd, 0, 0);
	free_strs(path);
	return (check_file_permission(cmd, path_cmd, all));
}
