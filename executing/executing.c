/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:39:57 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/15 17:58:59 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

int	is_builtin(char *token)
{
	if (!token)
		return (0);
	if (ft_strcmp("export", token))
		return (EXPORT);
	if (ft_strcmp("echo", token))
		return (ECHO);
	if (ft_strcmp("exit", token))
		return (EXIT);
	if (ft_strcmp("unset", token))
		return (UNSET);
	if (ft_strcmp("env", token))
		return (ENV);
	if (ft_strcmp("pwd", token))
		return (PWD);
	if (ft_strcmp("cd", token))
		return (CD);
	return (0);
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, SIG_IGN);  // Ignore Ctrl+C in parent
	signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+\ in parent
}

void	restore_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);  // Restore default Ctrl+C behavior
	signal(SIGQUIT, SIG_DFL); // Restore default Ctrl+\ behavior
}

void	close_parent_pipes(t_all *all)
{
	if (all->first->next)
	{
		// Close write end of current pipe if there's a next command
		close(all->first->pipe_fd[1]);
	}
	if (all->first->prev)
	{
		// Close read end of previous pipe if this isn't the first command
		close(all->first->prev->pipe_fd[0]);
	}
}

void	executing(t_all *all)
{
	t_data	*save;
	int		builtin;

	save = all->first;
	setup_signal_handlers();
	
	while (all->first)
	{
		if (all->first->next)
		{
			if (pipe(all->first->pipe_fd) == -1)
			{
				perror("pipe");
				ft_exit(all, NULL);
			}
		}
		
		if (setup_redirections(all))
		{
			perror("redirection error");
			ft_exit(all, NULL);
		}
		
		builtin = is_builtin(all->first->cmds->token);
		if (builtin != 0)
			all->status = builtin_caller(all, builtin);
		else
			all->status = shell_cmd(all);
		
		close_parent_pipes(all);
		
		all->first = all->first->next;
		if (reset_std_descriptors())
		{
			perror("reset descriptors");
			ft_exit(all, NULL);
		}
	}
	
	restore_signal_handlers();
	all->first = save;
	free_new_line(all);
	
	if (!all->first)
		return (ft_exit(all, NULL));
	return ;
}