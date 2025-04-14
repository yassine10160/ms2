/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:27 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/14 15:25:08 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"



int	ft_exit(t_all *all, char *token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (!is_digit(token[i]))
		{
			free_all(all);
			printf("exit\n");
			printf("exit : %s : numeric argument required", token);
			exit(2);
		}
	}
	exit()
}