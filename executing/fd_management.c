/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:53:08 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/15 17:59:08 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_input_redirection(t_all *all)
{
	if (all->first->fd_in != 0)
	{
		if (dup2(all->first->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 input redirection");
			return (1);
		}
		close(all->first->fd_in);
		all->first->fd_in = 0;
	}
	else if (all->first->prev)
	{
		if (dup2(all->first->prev->pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 pipe input");
			return (1);
		}
		// Read end of pipe will be closed in close_parent_pipes
	}
	return (0);
}

int	setup_output_redirection(t_all *all)
{
	if (all->first->fd_out != 1)
	{
		if (dup2(all->first->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 output redirection");
			return (1);
		}
		close(all->first->fd_out);
		all->first->fd_out = 1;
	}
	else if (all->first->next)
	{
		if (dup2(all->first->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe output");
			return (1);
		}
		// Write end of pipe will be closed in close_parent_pipes
	}
	return (0);
}

int	setup_redirections(t_all *all)
{
	if (setup_input_redirection(all))
		return (1);
	if (setup_output_redirection(all))
		return (1);
	return (0);
}

int	reset_std_descriptors(void)
{
	int	saved_stdin;
	int	saved_stdout;
	
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
	{
		perror("dup stdin");
		return (1);
	}
	
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		close(saved_stdin);
		perror("dup stdout");
		return (1);
	}
	
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		close(saved_stdin);
		close(saved_stdout);
		perror("dup2 stdin reset");
		return (1);
	}
	
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		close(saved_stdin);
		close(saved_stdout);
		perror("dup2 stdout reset");
		return (1);
	}
	
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}