/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:26:08 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/05 16:28:45 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export(t_env *env, int i)
{
	int	q;

	while (env->prev)
		env = env->prev;
	while (env->next)
	{
		printf("export ");
		i = 0;
		q = 0;
		while (env->line[i])
		{
			if ((i > 0) && (env->line[i - 1] == '='))
			{
				printf("\"");
				q++;
			}
			printf("%c", env->line[i]);
			i++;
		}
		if (q == 1)
			printf("\"");
		printf("\n");
		env = env->next;
	}
	return (0);
}

int	ft_export(t_env *env, t_cmds *cmds)
{
	char	*var_name;
	t_env	*save;

	if (!cmds || !cmds->token)
		return (print_export(env, 0));
	var_name = get_var_name(cmds->token);
	if (!var_name)
		return (2);
	if (!is_valid_identifier(var_name, cmds->token))
	{
		free(var_name);
		return (1);
	}
	save = find_in_env(env, var_name);
	free(var_name);
	if (!save)
	{
		if (add_lst_str(env, cmds->token))
			return (2);
	}
	else if (modify_line(save, cmds->token))
		return (2);
	return (0);
}
