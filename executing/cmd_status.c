/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:10:31 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/21 14:21:57 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
