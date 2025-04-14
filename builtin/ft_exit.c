/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:27 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/14 16:03:47 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

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

void	ft_exit(t_all *all, t_cmds *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->next)
	{
		free_all(all);
		exit(0);
	}
	cmd = cmd->next;
	while (cmd->token && cmd->token[i])
	{
		if (i == 0 && cmd->token[i] == '-')
			i++;
		else if (!is_digit(cmd->token[i]))
		{
			free_all(all);
			printf("exit\n");
			printf("exit : %s : numeric argument required", cmd->token);
			exit(2);
		}
	}
	free_all(all);
	exit(ft_atoi(cmd->token) % 256);
}

// int main()
// {
// 	ft_exit(NULL, "12345");
// }