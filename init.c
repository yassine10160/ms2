/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:53:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 15:09:46 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_cmds	*init_cmds(void)
{
	t_cmds	*cmds;

	cmds = ft_calloc(1, sizeof(struct s_cmds));
	if (!cmds)
		return (NULL);
	return (cmds);
}

t_data	*init_data(void)
{
	t_data	*data;
	int		fd_pipe[2];

	data = ft_calloc(1, sizeof(struct s_data));
	if (!data)
		return (NULL);
	data->cmds = init_cmds();
	if (!data->cmds)
	{
		free(data);
		return (NULL);
	}
	if (pipe(fd_pipe) == -1)
	{
		free(data->cmds);
		free(data);
		return (NULL);
	}
	data->fd_out = 1;
	data->pipe_fd[0] = fd_pipe[0];
	data->pipe_fd[1] = fd_pipe[1];
	return (data);
}

t_all	*init_all(void)
{
	t_all	*all;

	all = ft_calloc(1, sizeof(struct s_all));
	if (!all)
		return (NULL);
	all->first = init_data();
	if (!all->first)
	{
		free(all);
		return (NULL);
	}
	return (all);
}

t_cmds	*add_next_cmds(t_cmds *current)
{
	t_cmds	*new;

	new = init_cmds();
	if (!new)
		return (NULL);
	new->prev = current;
	current->next = new;
	return (new);
}

t_data	*add_next_data(t_data *current)
{
	t_data	*new;

	new = init_data();
	if (!new)
		return (NULL);
	current->next = new;
	new->prev = current;
	return (new);
}

int  main()
{
	t_all	*all;

	all = init_all();
	if (all)
	{
		printf("%d\n%s\n", all->first->fd_out, all->first->cmds->cmd);
		free_all(all);
	}
}

