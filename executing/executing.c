/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:39:57 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/15 13:32:46 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	is_builtin(char *token)
{
	if (ft_strcmp("export", token))
		return (EXPORT);
	if (ft_strcmp("echo", token))
		return (ECHO);
	if (ft_strcmp("exit", token))
		return (EXIT);
	if (ft_strcmp("unset", token))
		return (UNSET);
	if (ft_strcmp("env", token))
		return (ENV);
	if (ft_strcmp("pwd", token))
		return (PWD);
	if (ft_strcmp("cd", token))
		return (CD);
	return (0);
}

int	fd_handle(t_data *data, int *f_out, int *f_in)
{
	if (data->fd_in != 1 || f_in != 0)
	{
		if (dup2(STDIN_FILENO, data->fd_in) == -1)
			return (1);
		*f_in = 1;
	}
	if (data->fd_out != 0 || f_out != 0)
	{
		if (dup2(STDOUT_FILENO, data->fd_out) == -1)
			return (1);
		*f_out = 1;
	}
	return (0);
}

void	executing(t_all *all)
{
	int		builtin;
	t_all	*save;
	int		f_out;
	int		f_in;

	f_out = 0;
	f_in = 0;
	save = all;
	while (all->first)
	{
		if (fd_handle(all->first, &f_out, &f_in))
			return (ft_exit(save, NULL));
		builtin = is_builtin(all->first->cmds->token);
		if (builtin != 0)
			builtin_caller(all, builtin, save);
		else
			shell_cmd(all, save);
		all->first = all->first->next;
	}
	all = save;
}

// int main()
// {
// 	char	*str = ft_strdup("pwd");
// 	printf("%d", is_builtin(str));
// }