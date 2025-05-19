/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:36:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/19 23:21:34 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*remove_node(t_env *node)
{
	t_env	*prev;
	t_env	*next;

	if (node)
	{
		prev = node->prev;
		next = node->next;
		if (prev)
			prev->next = next;
		if (next)
			next->prev = prev;
		if (node->line)
			free(node->line);
		free(node);
		if (prev)
			return (prev);
		if (next)
			return (next);
		return (NULL);
	}
	return (NULL);
}

int	ft_unset(t_env *env, t_cmds *cmd)
{
	t_env	*save;
	t_cmds	*ptr;

	if (cmd->next)
	{
		ptr = cmd;
		cmd = cmd->next;
		while (cmd)
		{
			save = find_in_env(env, cmd->token);
			if (save)
				env = remove_node(save);
			cmd = cmd->next;
		}
		cmd = ptr;
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
