/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:23:59 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/18 13:23:11 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

int	is_printable(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}


void	ft_env(t_env *env)
{
	t_env	*save;

	save = env;
	while (env->prev)
		env = env->prev;
	while (env)
	{
		if (is_printable(env->line))
			printf("%s\n", env->line);
		env = env->next;
	}
	env = save;
}