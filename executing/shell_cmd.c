/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:24:31 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/15 13:51:11 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	shell_cmd(t_all *all, t_all *save)
{
	char	**cmds;
	char	**env;

	cmds = cmds_to_strs(all->first->cmds, 1, 0);
	if (!cmds)
		return (ft_exit(save, NULL));
	env = env_to_strs(all->env, 0, 1);
	if (!env)
	{
		free_strs(cmds);
		return (ft_exit(save, NULL));
	}
	
	return ;
}