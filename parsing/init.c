/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:27:43 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/29 13:16:03 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data *init_data(int mode)
{
	t_data *data;

	data = ft_calloc(1, sizeof(struct s_data));
	if (!data)
		return (NULL);
	data->cmds = ft_calloc(1, sizeof(struct s_cmds));
	if (!data->cmds)
	{
		free(data);
		return (NULL);
	}
	data->pipe_fd[0] = -2;
	data->pipe_fd[1] = -2;
	if (mode == PIPE)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			free(data->cmds);
			free(data);
			return (NULL);
		}
		data->fd_in = data->pipe_fd[0];
		data->fd_out = data->pipe_fd[1];
	}
	else
	{
		data->fd_in = 0;
		data->fd_out = 1;
	}
	return (data);
}

t_all *init_all(char **env)
{
	t_all *all;

	all = ft_calloc(1, sizeof(struct s_all));
	if (!all)
		return (NULL);
	all->first = init_data(NONE);
	// all->first->next = NULL;
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
	all->pids = NULL;
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
	new->next = NULL;
	current->next = new;
	return (new);
}

t_data *add_next_data(t_data *current)
{
	t_data *new;

	new = NULL;
	// new = ft_calloc(1, sizeof(t_data));
	new = init_data(PIPE);
	if (!new)
		return (NULL);
	current->next = new;
	new->prev = current;
	new->next = NULL;
	// printf("current: %s\n", new->prev->cmds->next->token);
	return (new);
}

t_cmds *remove_cmd(t_cmds *current)
{
	t_cmds *next;
	t_cmds *prev;

	if (!current)
		return (NULL);
	prev = current->prev;
	next = current->next;
	if (prev)
		prev->next = next;
	else if (next)
		next->prev = NULL;
	if (next)
		next->prev = prev;
	else if (prev)
		prev->next = NULL;
	if (current && current->token)
	{
		free(current->token);
		free(current);
	}
	if (next->token)
	{
		// printf("Here next %s\n", next->token);
		current = next;
	}
	else
	{
		// printf("Here prev %s\n", prev->token);
		current = prev;
	}
	return (current);
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