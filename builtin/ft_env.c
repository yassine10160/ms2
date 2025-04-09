/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:23:59 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 13:25:36 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

void	ft_env(t_env *env)
{
	while (env->prev)
		env = env->prev;
	while (env->next)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
}