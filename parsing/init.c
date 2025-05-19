/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:27:43 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/05/19 15:06:01 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(struct s_data));
	if (!data)
		return (NULL);
	data->cmds = ft_calloc(1, sizeof(struct s_cmds));
	if (!data->cmds)
	{
		free(data);
		return (NULL);
	}
	if (pipe(data->pipe_fd) == -1)
	{
		free(data->cmds);
		free(data);
		return (NULL);
	}
	data->fd_in = 0;
	data->fd_out = 1;
	return (data);
}

t_all	*init_all(char **env)
{
	t_all	*all;

	all = ft_calloc(1, sizeof(struct s_all));
	if (!all)
		exit(1);
	all->first = init_data();
	if (!all->first)
	{
		free(all);
		exit(1);
	}
	all->status = 0;
	all->env = env_to_struct(env);
	if (!all->env)
	{
		free_data(all->first);
		free(all);
		exit(1);
	}
	all->fd_save[0] = -1;
	all->fd_save[1] = -1;
	all->pids = NULL;
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
	new->next = NULL;
	current->next = new;
	return (new);
}

t_data	*add_next_data(t_data *current)
{
	t_data	*new;

	new = NULL;
	new = init_data();
	if (!new)
		return (NULL);
	current->next = new;
	new->prev = current;
	new->next = NULL;
	return (new);
}

t_cmds	*remove_cmd(t_cmds *current)
{
	t_cmds	*next;
	t_cmds	*prev;

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
	if (next && next->token)
		current = next;
	else
		current = prev;
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
// 		tmp = add_prev_cmds(tmp);
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