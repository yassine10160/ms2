/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:39:57 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/15 15:16:20 by dorianmazar      ###   ########.fr       */
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
	t_data	*save;
	int		builtin;
	int		f_out;
	int		f_in;

	f_out = 0;
	f_in = 0;
	save = all->first;
	while (all->first)
	{
		if (fd_handle(all->first, &f_out, &f_in))
			return (ft_exit(all, NULL));
		builtin = is_builtin(all->first->cmds->token);
		if (builtin != 0)
			all->status = builtin_caller(all, builtin);
		else
			all->status = shell_cmd(all);
		all->first = all->first->next;
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