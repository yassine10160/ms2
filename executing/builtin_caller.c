/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_caller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:16:05 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/22 15:17:32 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	caller_next(t_all *all, int builtin)
{
	t_cmds	*save;

	save = all->first->cmds;
	if (builtin == CD)
	{
		if (all->first->cmds->next)
			if (ft_cd(all->env, all->first->cmds->next->token) == 2)
				ft_exit(all, NULL);
	}
	else if (builtin == EXPORT)
	{
		while (all->first->cmds->next)
		{
			all->first->cmds = all->first->cmds->next;
			ft_export(all->env, all->first->cmds->token);
		}
		all->first->cmds = save;
	}
	return (0);
}

int	builtin_caller(t_all *all, int builtin)
{
	if (builtin == EXIT)
		ft_exit(all, all->first->cmds->next);
	else if (builtin == ECHO)
		ft_echo(all->first->cmds->next);
	else if (builtin == UNSET)
		ft_unset(all->env, all->first->cmds);
	else if (builtin == ENV)
		ft_env(all->env);
	else if (builtin == PWD)
	{
		if (ft_pwd())
			ft_exit(all, NULL);
	}
	else
		return (caller_next(all, builtin));
	return (0);
}
