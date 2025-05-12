/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:52:41 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/12 14:30:24 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "./") == 1)
		put_str_error(cmd, "No such file or directory", 2);
	else
		put_str_error(cmd, "command not found", 2);
}

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

int	check_local(char *cmd, char **path_cmd)
{
	char	*pwd;

	pwd = get_pwd(NULL);
	if (!pwd)
	{
		*path_cmd = NULL;
		return (0);
	}
	*path_cmd = ft_strcat(ft_strcat(pwd, "/", 0, 0), cmd, 0, 0);
	free(pwd);
	if (!*path_cmd)
		return (0);
	if (access(*path_cmd, F_OK | X_OK) == 0)
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
	if ((!path || !cmd) && !check_local(cmd, &path_cmd))
	{
		if (!path)
			put_str_fd("Error : PATH not defined\n", 2);
	}
	else if (path && cmd && !path_cmd)
	{
		i = index_path_cmd(cmd, path);
		if (path)
			free_strs(path);
		if (i == -1)
		{
			no_cmd(cmd);
			all->status = 127;
		}
		else
			path_cmd = ft_strcat(path[i], cmd, 0, 0);
	}
	return (path_cmd);
}
