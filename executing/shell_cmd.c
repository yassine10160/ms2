/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:24:31 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/15 18:00:44 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>

int	print_error(char *cmd, char *message)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	return (127);
}

void	child_process(char **cmds, char **env, char *path_cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		// Child process
		execve(path_cmd, cmds, env);
		// If execve returns, there was an error
		perror(cmds[0]);
		free_strs(cmds);
		free_strs(env);
		free(path_cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
		// Parent process - wait for child to complete
		waitpid(pid, &status, 0);
	}
}

int	check_path_cmd(t_all *all, char *cmd, char **env)
{
	(void)all;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (0);
		free_strs(env);
		return (print_error(cmd, "Permission denied"));
	}
	free_strs(env);
	return (print_error(cmd, "command not found"));
}

int	shell_cmd(t_all *all)
{
	char	**cmds;
	char	**env;
	char	*path_cmd;
	int		status;

	cmds = cmds_to_strs(all->first->cmds, 1, 0);
	if (!cmds)
		ft_exit(all, NULL);
	
	env = env_to_strs(all->env, 0, 1);
	if (!env)
	{
		free_strs(cmds);
		ft_exit(all, NULL);
	}
	
	// Check if the command is an absolute or relative path
	if (cmds[0][0] == '/' || cmds[0][0] == '.')
	{
		path_cmd = ft_strdup(cmds[0]);
		if (!path_cmd)
		{
			free_strs(cmds);
			free_strs(env);
			ft_exit(all, NULL);
		}
		status = check_path_cmd(all, path_cmd, env);
		if (status != 0)
		{
			free_strs(cmds);
			return (status);
		}
	}
	else
	{
		path_cmd = get_path_cmd(cmds[0], get_path_env(all->env));
		if (!path_cmd)
		{
			status = print_error(cmds[0], "command not found");
			free_strs(env);
			free_strs(cmds);
			return (status);
		}
	}
	
	child_process(cmds, env, path_cmd);
	free(path_cmd);
	free_strs(cmds);
	free_strs(env);
	return (0);
}