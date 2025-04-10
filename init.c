/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:53:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/10 10:03:33 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	init_cmds(t_cmds *cmds)
{
	cmds = ft_calloc(1, sizeof(struct s_cmds));
	if (!cmds)
		return (NULL);
	return (cmds);
}

void	init_data(t_data *data)
{
	int		fd_pipe[2];

	data = ft_calloc(1, sizeof(struct s_data));
	if (!data)
		return (NULL);
	init_cmds(data->cmds);
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

void	init_all(t_all *all)
{
	all = ft_calloc(1, sizeof(struct s_all));
	if (!all)
		return (NULL);
	init_data(all->first);
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

	init_cmds(new);
	if (!new)
		return (NULL);
	new->prev = current;
	current->next = new;
	return (new);
}

t_data	*add_next_data(t_data *current)
{
	t_data	*new;

	init_data(new);
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
