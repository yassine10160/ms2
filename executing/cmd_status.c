/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:10:31 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/20 00:17:16 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_exec_error(char *cmd, char *path_cmd, t_all *all, int type)
{
	if (type == 0)
	{
		put_str_error(cmd, "Permission denied", 2);
		all->status = 126;
	}
	else if (type == 1)
	{
		put_str_error(cmd, "Is a directory", 2);
		all->status = 126;
	}
	free(path_cmd);
	return (NULL);
}

int	extract_exit_status(int wait_status)
{
	if (WIFEXITED(wait_status))
		return (WEXITSTATUS(wait_status));
	else if (WIFSIGNALED(wait_status))
		return (128 + WTERMSIG(wait_status));
	return (1);
}

void	wait_for_processes(t_all *all, int *pids, int cmd_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (i == cmd_count - 1)
				all->status = extract_exit_status(status);
		}
		i++;
	}
}

int	*init_pids_array(int cmd_count)
{
	int	*pids;
	int	i;

	pids = malloc(sizeof(int) * cmd_count);
	if (!pids)
		return (NULL);
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = -1;
		i++;
	}
	return (pids);
}
