/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:36:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/28 12:35:36 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_node(t_env **current)
{
	t_env	*prev;
	t_env	*next;

	if (!(*current))
		return ;
	prev = (*current)->prev;
	next = (*current)->next;
	if (next && !next->line && !prev)
	{
		free(next);
		next = NULL;
	}
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if ((*current) && (*current)->line)
	{
		free((*current)->line);
		free((*current));
	}
	if (next && next->line)
		(*current) = next;
	else
		(*current) = prev;
}

int	process_unset_token(t_env **env, char *token)
{
	t_env	*save;

	save = find_in_env(*env, token);
	if (save)
	{
		remove_node(&save);
		if (save)
		{
			while (save->prev)
				save = save->prev;
			*env = save;
		}
		else
		{
			*env = ft_calloc(sizeof(t_env), 1);
			if (!*env)
				return (1);
		}
	}
	return (0);
}

int	ft_unset(t_env **env, t_cmds *cmd)
{
	t_cmds	*ptr;
	int		result;

	if (!cmd || !cmd->next)
		return (0);
	ptr = cmd;
	cmd = cmd->next;
	while (cmd)
	{
		result = process_unset_token(env, cmd->token);
		if (result != 0)
			return (result);
		cmd = cmd->next;
	}
	cmd = ptr;
	return (0);
}
