/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:03:13 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/03 16:59:31 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_env(t_env *env)
{
	t_env *save;

	if (!env)
		return;
	while (env->prev)
		env = env->prev;
	while (env)
	{
		if (env->line)
			free(env->line);
		save = env;
		env = env->next;
		free(save);
	}
}

void free_cmds(t_cmds *cmds)
{
	t_cmds *save;

	if (!cmds)
		return;
	while (cmds->prev)
		cmds = cmds->prev;
	while (cmds)
	{
		if (cmds->token)
			free(cmds->token);
		save = cmds;
		cmds = cmds->next;
		if (save)
			free(save);
	}
}

void free_data(t_data *data)
{
	t_data *save;

	if (!data)
		return;
	while (data->prev)
		data = data->prev;
	while (data)
	{
		free_cmds(data->cmds);
		if (data->fd_in != 0)
			close(data->fd_in);
		if (data->fd_out != 1)
			close(data->fd_out);
		if (data->pipe_fd[0] != -2)
			close(data->pipe_fd[0]);
		if (data->pipe_fd[1] != -2)
			close(data->pipe_fd[1]);
		save = data;
		data = data->next;
		free(save);
	}
}

void free_all(t_all *all)
{
	if (!all)
		return;
	if (all->f_here_doc)
		unlink(".tmp");
	if (all->pids)
		free(all->pids);
	free_env(all->env);
	free_data(all->first);
	free(all);
	all = NULL;
}

void free_new_line(t_all *all)
{
	if (all->f_here_doc)
		unlink(".tmp");
	all->f_here_doc = 0;
	free_data(all->first);
	all->first = init_data();
}
