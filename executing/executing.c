/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:39:57 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/19 22:38:29 by mazakov          ###   ########.fr       */
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

int	builtin_child(t_all *all, int builtin)
{
	int	pid;
	int	rtn;

	pid = fork();
	if (pid < 0)
		handle_fork_error(NULL, NULL, NULL, all);
	if (pid == 0)
	{
		rtn = builtin_caller(all, builtin);
		free_all(all);
		exit(rtn);
	}
	return (pid);
}

void	execute_cmd(t_all *all, int *pids, int i)
{
	int	builtin;

	if (!all->first || !all->first->cmds || !all->first->cmds->token)
	{
		all->status = 0;
		if (g_stop != 0)
			all->status = 130;
		return ;
	}
	if (!setup_redirections(all, &all->fd_save[0], &all->fd_save[1]))
		ft_exit(all, NULL);
	if (all->first->fd_in == -1 || all->first->fd_out == -1)
		all->status = 1;
	else if (all->first->cmds->token)
	{
		builtin = is_builtin(all->first->cmds->token);
		if (builtin != 0 && !all->first->next && !all->first->prev)
			all->status = builtin_caller(all, builtin);
		else if (builtin != 0)
			pids[i] = builtin_child(all, builtin);
		else
			pids[i] = shell_cmd(all);
	}
	if (!reset_std_descriptors(&all->fd_save[0], &all->fd_save[1]))
		ft_exit(all, NULL);
}

void	executing(t_all *all, int i)
{
	t_data	*save;
	int		cmd_count;

	if (!all->first->cmds && !all->first->next)
		free_new_line(all);
	else
	{
		save = all->first;
		cmd_count = count_cmds(all);
		all->pids = init_pids_array(cmd_count);
		if (!all->pids)
			ft_exit(all, NULL);
		i = 0;
		while (all->first)
		{
			execute_cmd(all, all->pids, i);
			all->first = all->first->next;
			i++;
		}
		wait_for_processes(all, all->pids, cmd_count);
		all->first = save;
		free_new_line(all);
	}
	if (!all->first)
		ft_exit(all, NULL);
}
