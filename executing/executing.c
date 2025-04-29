/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:39:57 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/29 15:44:15 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *token)
{
	if (ft_strcmp("export", token) == 2)
		return (EXPORT);
	if (ft_strcmp("echo", token) == 2)
		return (ECHO);
	if (ft_strcmp("exit", token) == 2)
		return (EXIT);
	if (ft_strcmp("unset", token) == 2)
		return (UNSET);
	if (ft_strcmp("env", token) == 2)
		return (ENV);
	if (ft_strcmp("pwd", token) == 2)
		return (PWD);
	if (ft_strcmp("cd", token) == 2)
		return (CD);
	return (0);
}
int	count_cmds(t_all *all)
{
	t_data	*save;
	int		count;

	save = all->first;
	count = 0;
	while (all->first)
	{
		count++;
		all->first = all->first->next;
	}
	all->first = save;
	return (count);
}

void	execute_cmd(t_all *all, int *pids, int i, int cmd_count)
{
	int	builtin;

	if (setup_redirections(all))
		ft_exit(all, NULL);
	(void)cmd_count;
	if (all->first->cmds->token)
	{
		builtin = is_builtin(all->first->cmds->token);
		if (builtin != 0)
		{
			// if (cmd_count == 1)
				all->status = builtin_caller(all, builtin);
			// else
			// {
			// 	pids[i] = fork();
			// 	if (pids[i] == 0)
			// 	{
			// 		all->status = builtin_caller(all, builtin);
			// 		exit(0) ;
			// 	}
			// }
		}
		else
			pids[i] = shell_cmd(all);
	}
	if (reset_std_descriptors())
		ft_exit(all, NULL);
}

void	executing(t_all *all)
{
	t_data	*save;
	int		cmd_count;
	int		i;

	save = all->first;
	cmd_count = count_cmds(all);
	all->pids = init_pids_array(cmd_count);
	if (!all->pids)
		ft_exit(all, NULL);
	i = 0;
	while (all->first)
	{
		execute_cmd(all, all->pids, i, cmd_count);
		all->first = all->first->next;
		i++;
	}
	wait_for_processes(all, all->pids, cmd_count);
	all->first = save;
	free_new_line(all);
	if (!all->first)
		ft_exit(all, NULL);
}
