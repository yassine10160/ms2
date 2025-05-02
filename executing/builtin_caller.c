/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_caller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:16:05 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/02 18:06:55 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	caller_next(t_all *all, int builtin)
{
	t_cmds	*save;
	int		rtn;

	save = all->first->cmds;
	if (builtin == CD)
	{
		if (all->first->cmds->next)
			return (ft_cd(all->env, all->first->cmds->next->token));
	}
	else if (builtin == EXPORT)
	{
		all->first->cmds = all->first->cmds->next;
		while (all->first->cmds)
		{
			rtn = ft_export(all->env, all->first->cmds);
			if (!all->first->cmds->next || !all->first->cmds->next->token)
				break ;
			all->first->cmds = all->first->cmds->next;
		}
		all->first->cmds = save;
		return (rtn);
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
		return (ft_pwd());
	else
		return (caller_next(all, builtin));
	return (0);
}
