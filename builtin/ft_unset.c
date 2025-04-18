/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:36:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/18 14:45:16 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void remove_node(t_env *node)
{
	t_env *prev;
	t_env *next;

	if (node)
	{
		prev = node->prev;
		next = node->next;
		prev->next = next;
		if (next)
			next->prev = prev;
		if (node->line)
			free(node->line);
		free(node);
	}
}

int ft_unset(t_env *env, t_cmds *cmd)
{
	t_env *save;

	if (cmd->next)
	{
		cmd = cmd->next;
		while (cmd->next)
		{
			save = find_in_env(env, cmd->token);
			if (save)
				remove_node(save);
			cmd = cmd->next;
		}
		save = find_in_env(env, cmd->token);
		if (save)
			remove_node(save);
	}
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_all *all;

// 	(void)ac;
// 	(void)av;
// 	all = init_all(env);
// 	all->first->cmds->token = ft_strdup("a");
// 	ft_export(all->env, ft_strdup("a=salut"));
// 	ft_env(all->env);
// 	ft_unset(all->env, all->first->cmds);
// 	ft_env(all->env);
// 	ft_exit(all, NULL);
// }
