/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:53:08 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/02 20:26:47 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_input_redirection(t_all *all)
{
	if (all->first->fd_in == -1)
		return (0);
	if (all->first->fd_in != 0)
	{
		if (dup2(all->first->fd_in, STDIN_FILENO) == -1)
			return (1);
		close(all->first->fd_in);
		all->first->fd_in = 0;
	}
	else if (all->first->prev)
	{
		if (dup2(all->first->prev->pipe_fd[0], STDIN_FILENO) == -1)	
			return (1);
		close(all->first->prev->pipe_fd[0]);
		all->first->prev->pipe_fd[0] = -2;
	}
	return (0);
}

int	setup_output_redirection(t_all *all)
{
	if (all->first->fd_out != 1)
	{
		if (dup2(all->first->fd_out, STDOUT_FILENO) == -1)
			return (1);
		close(all->first->fd_out);
		all->first->fd_out = 1;
	}
	else if (all->first->next)
	{
		if (dup2(all->first->pipe_fd[1], STDOUT_FILENO) == -1)
			return (1);
		close(all->first->pipe_fd[1]);
		all->first->pipe_fd[1] = -2;
	}
	return (0);
}

int	setup_redirections(t_all *all, int *fd_save_in, int *fd_save_out)
{
	*fd_save_in = dup(STDIN_FILENO);
	*fd_save_out = dup(STDOUT_FILENO);
	if (setup_input_redirection(all))
		return (0);
	if (setup_output_redirection(all))
		return (0);
	return (1);
}

int	reset_std_descriptors(int *fd_save_in, int *fd_save_out)
{
	if (dup2(*fd_save_in, STDIN_FILENO) == -1)
		return (0);
	if (dup2(*fd_save_out, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}
