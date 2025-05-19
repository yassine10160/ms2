/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:27 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/19 22:42:19 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(char *str)
{
	int	nb;
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (!str)
		return (0);
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	nb = 0;
	while (str && str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * flag);
}

void	loop_exit(t_all *all, char *cmd, int *i)
{
	if (*i == 0 && (cmd[*i] == '-' || cmd[*i] == '+'))
		*i = *i + 1;
	if (!is_digit(cmd[*i]))
	{
		put_str_fd("exit\n", 2);
		put_str_function("exit", cmd, "numeric argument required", 2);
		free_all(all);
		exit(2);
	}
	*i = *i + 1;
}
int	process_exit_args(t_all *all, t_cmds *cmd)
{
	int	tmp;
	int	i;
	
	i = 0;
	if (!cmd || !cmd->token)
		return (0);
	while (cmd->token[i])
		loop_exit(all, cmd->token, &i);
	if (cmd->next && cmd->next->token)
	{
		put_str_fd("exit\n", 2);
		put_str_error("exit", "too many arguments", 2);
		return (1);
	}
	else
	{
		tmp = ft_atoi(cmd->token);
		put_str_fd("exit\n", 2);
		free_all(all);
		exit(tmp % 256);
	}
}

int	ft_exit(t_all *all, t_cmds *cmd)
{
	int	tmp;
	
	if (!cmd || !cmd->next)
	{
		tmp = all->status;
		put_str_fd("exit\n", 2);
		free_all(all);
		exit(tmp);
	}
	if (process_exit_args(all, cmd))
		return (1);
	tmp = all->status;
	put_str_fd("exit\n", 2);
	free_all(all);
	exit(tmp);
	return (0);
}
