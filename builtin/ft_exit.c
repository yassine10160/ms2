/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:27 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/13 19:22:03 by dmazari          ###   ########.fr       */
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
	if (*i == 0 && cmd[*i] == '-')
		*i = *i + 1;
	if (!is_digit(cmd[*i]))
	{
		put_str_function("exit", cmd, "numeric argument required", 2);
		put_str_fd("exit\n", 2);
		free_all(all); 
		exit(2);
	}
	*i = *i + 1;
}

void	ft_exit(t_all *all, t_cmds *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->next || !cmd->next->token)
	{
		put_str_fd("exit\n", 2);
		free_all(all);
		exit(0);
	}
	cmd = cmd->next;
	while (cmd && cmd->token && cmd->token[i])
	{
		loop_exit(all, cmd->token, &i);
	}
	if (!cmd->token[i] && cmd->next && cmd->next->token)
		put_str_error("exit", "too many arguments", 2);
	else
	{
		i = ft_atoi(cmd->token);
		put_str_fd("exit\n", 2);
		free_all(all);
		exit(i % 256);
	}
}

// int main()
// {
// 	ft_exit(NULL, "12345");
// }