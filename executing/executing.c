/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:39:57 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/20 14:42:07 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *token)
{
	if (ft_strcmp("export", token) == 2)
		return (EXPORT);
	if (ft_strcmp("echo", token) == 2)
		return (ECHO);
	if (ft_strcmp("exit", token) == 2)
		return (EXIT);
	if (ft_strcmp("unset", token) == 2)
		return (UNSET);
	if (ft_strcmp("env", token) == 2)
		return (ENV);
	if (ft_strcmp("pwd", token) == 2)
		return (PWD);
	if (ft_strcmp("cd", token) == 2)
		return (CD);
	return (0);
}

void	executing(t_all *all)
{
	t_data	*save;
	int		builtin;

	save = all->first;
	while (all->first)
	{
	// 	if (setup_redirections(all))
	// 		ft_exit(all, NULL);
		if (all->first->cmds->token)
		{
			builtin = is_builtin(all->first->cmds->token);
			if (builtin != 0)
				all->status = builtin_caller(all, builtin);
			else
				all->status = shell_cmd(all);
		}
		all->first = all->first->next;
		// if (reset_std_descriptors())
		// 	ft_exit(all, NULL);
	}
	all->first = save;
	free_new_line(all);
	if (!all->first)
		return (ft_exit(all, NULL));
	return ;
}

// int main()
// {
// 	char	*str = ft_strdup("pwd");
// 	printf("%d", is_builtin(str));
// }