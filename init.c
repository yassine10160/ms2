/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:53:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 20:03:59 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_cmds(t_cmds *cmds)
{
	cmds = malloc(sizeof(struct s_cmds));
	if (!cmds)
		return;
	cmds->token = NULL;
	cmds->prev = NULL;
	cmds->next = NULL;
}

void init_data(t_data *data)
{
	int fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return;
	data = malloc(sizeof(struct s_data));
	if (!data)
		return;
	data->cmds = NULL;
	data->fd_in = 0;
	data->fd_out = 1;
	data->prev = NULL;
	data->next = NULL;
	data->pipe_fd[0] = fd_pipe[0];
	data->pipe_fd[1] = fd_pipe[1];
	init_cmds(data->cmds);
}

void init_all(t_all *all)
{
	all = malloc(sizeof(struct s_all));
	if (!all)
		return;
	init_data(all->first);
}

// int  main()
// {
// 	t_data	*data;

// 	data = calloc(1, sizeof(struct s_data));
// 	if  (!data)
// 		printf("ko");
// 	else
// 	{
// 		printf("%d",data->fd_in);
// 	}
// }