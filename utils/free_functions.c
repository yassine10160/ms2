/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:03:13 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/10 10:47:38 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *env)
{
	t_env	*save;

	if (!env)
		return ;
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

	if (!cmds)
		return ;
	while (cmds->prev)
		cmds = cmds->prev;
	while (cmds)
	{
		if (cmds->token)
			free(cmds->token);
		save = cmds;
		cmds = cmds->next;
		free(save);
	}
}

void	free_data(t_data *data)
{
	t_data	*save;

	if (!data)
		return ;
	while (data->prev)
		data = data->prev;
	while (data)
	{
		free_cmds(data->cmds);
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
}

void	free_all(t_all *all)
{
	if (!all)
		return ;
	free_env(all->env);
	free_data(all->first);
	free(all);
	all = NULL;
}
