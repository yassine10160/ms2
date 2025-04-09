/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:03:13 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 13:11:59 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *env)
{
	t_env	*save;

	while (env->prev)
		env = env->prev;
	while (env->next)
	{
		if (env->line)
			free(env->line);
		save = env;
		env = env->next;
		free(save);
	}
	if (env)
		free(env);
}

void	free_cmds(t_cmds *cmds)
{
	t_cmds	*save;

	while (cmds->prev)
		cmds = cmds->prev;
	while (cmds->next)
	{
		if (cmds->cmd)
			free(cmds->cmd);
		save = cmds;
		cmds = cmds->next;
		free(save);
	}
	if (cmds)
		free(cmds);
}

void	free_data(t_data *data)
{
	t_data	*save;

	while (data->prev)
		data = data->prev;
	while (data->next)
	{
		free_cmds(&data->cmds);
		if (data->line)
			free(data->line);
		if (data->fd_in != 0)
			close(data->fd_in);
		if (data->fd_out != 1)
			close(data->fd_out);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		save = data;
		data = data->next;
		free(save);
	}
	if (data)
		free(data);
}

void	free_all(t_all *all)
{
	free_env(all->env);
	free_data(all->first);
	free(all);
}
