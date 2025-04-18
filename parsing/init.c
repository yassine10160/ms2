/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:53:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/18 14:44:59 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data *init_data()
{
	t_data *data;
	int fd_pipe[2];

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

t_all *init_all(char **env)
{
	t_all *all;

	all = ft_calloc(1, sizeof(struct s_all));
	if (!all)
		return (NULL);
	all->first = init_data();
	if (!all->first)
	{
		free(all);
		return (NULL);
	}
	all->status = 0;
	all->env = env_to_struct(env);
	if (!all->env)
	{
		free_data(all->first);
		free(all);
		return (NULL);
	}
	return (all);
}

t_cmds *add_next_cmds(t_cmds *current)
{
	t_cmds *new;

	new = NULL;
	new = ft_calloc(1, sizeof(struct s_cmds));
	if (!new)
		return (NULL);
	new->prev = current;
	current->next = new;
	return (new);
}

t_data *add_next_data(t_data *current)
{
	t_data *new;

	new = NULL;
	new = init_data();
	if (!new)
		return (NULL);
	current->next = new;
	new->prev = current;
	return (new);
}

void remove_cmd(t_cmds *current)
{
	t_cmds *next;
	t_cmds *prev;

	prev = current->prev;
	next = current->next;
	prev->next = next;
	if (next)
		next->prev = prev;
	printf("je suis la\n");
	if (current && current->token)
	{
		free(current->token);
		free(current);
	}
}

// int main(int ac, char **av, char **env)
// {
// 	t_all *all;
// 	t_cmds *tmp;

// 	all = init_all(env);
// 	printf("ok\n");
// 	(void)ac;
// 	(void)av;
// 	if (all)
// 	{
// 		tmp = all->first->cmds;
// 		tmp->token = ft_strdup("ls");
// 		printf("cmds: %s\n", tmp->token);
// 		tmp = add_next_cmds(tmp);
// 		tmp->token = ft_strdup(">");
// 		printf("cmds: %s\n", tmp->token);
// 		tmp = add_next_cmds(tmp);
// 		tmp->token = ft_strdup("a");
// 		printf("cmds: %s\n", tmp->token);
// 		remove_cmd(tmp->prev);
// 		printf("new cmds: %s\n", tmp->prev->token);
// 		remove_cmd(tmp);
// 		printf("new cmds: %s\n", tmp->token);
// 		// printf("new cmds: %s\n", tmp->next->next->token);
// 		// printf("%d\n%s\n", all->first->fd_out, all->env->line);
// 		// free_all(all);
// 	}
// }
