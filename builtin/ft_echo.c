/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:54 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/12 16:06:25 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n(t_cmds *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	if (cmd->token && cmd->token[0] == '-')
	{
		i++;
		if (!cmd->token[i])
			return (0);
		while (cmd->token[i] && cmd->token[i] == 'n')
			i++;
		if (!cmd->token[i])
			return (1);
	}
	return (0);
}

void	ft_echo(t_cmds *cmd)
{
	int	flag;

	flag = is_n(cmd->token);
	if (!cmd && !flag)
		printf("\n");
	if (!cmd)
		return ;
	if (flag)
		cmd = cmd->next;
	while (cmd->next && cmd->token)
	{
		printf("%s", cmd->token);
		if (cmd->next)
			printf(" ");
		cmd = cmd->next;
	}
	if (cmd->token)
		printf("%s", cmd->token);
	if (!flag)
		printf("\n");
}
