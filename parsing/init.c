/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:53:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/10 11:50:50 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*init_data()
{
	t_data	*data;
	int		fd_pipe[2];

	data = ft_calloc(1, sizeof(struct s_data));
	if (!data)
		return (NULL);
	data->cmds = ft_calloc(1, sizeof(struct s_cmds));
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

t_all	*init_all(char **env)
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
	all->env = env_to_struct(env);
	if (!all->env)
	{
		free_data(all->first);
		free(all);
		return (NULL);
	}
	return (all);
}

t_cmds	*add_next_cmds(t_cmds *current)
{
	t_cmds	*new;

	new = NULL;
	new = ft_calloc(1, sizeof(struct s_cmds));
	if (!new)
		return (NULL);
	new->prev = current;
	current->next = new;
	return (new);
}

t_data	*add_next_data(t_data *current)
{
	t_data	*new;

	new = NULL;
	init_data(new);
	if (!new)
		return (NULL);
	current->next = new;
	new->prev = current;
	return (new);
}

// int  main(int ac, char **av, char **env)
// {
// 	t_all	*all;

// 	all = init_all(env);
// 	printf("ok");
// 	if (all)
// 	{
// 		printf("%d\n%s\n", all->first->fd_out, all->env->line);
// 		free_all(all);
// 	}
