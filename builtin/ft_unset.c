/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:36:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 13:38:26 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_node(t_env *node)
{
	t_env	*prev;
	t_env	*next;

	prev = node->prev;
	next = node->next;
	prev->next = next;
	next->prev = prev;
	if (node->line)
		free(node->line);
	free(node);
}

int	ft_unset(t_env *env, char *var_name)
{
	t_env	*save;

	save = find_in_env(env, var_name);
	if (save)
		remove_node(save);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	*str = ft_strdup("asalut");
// 	t_env *ev;

// 	ev = env_to_struct(env);
// 	ft_export(ev, str);
// 	ft_env(ev);
// 	ft_unset(ev, "a");
// 	ft_env(ev);
// 	free_new_env(ev);
// }
