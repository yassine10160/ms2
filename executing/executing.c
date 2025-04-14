/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:39:57 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/14 13:40:34 by mazakov          ###   ########.fr       */
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

int	fd_handle(t_data *data)
{
	if (data->fd_in != 1)
	{
		if (dup2(STDIN_FILENO, data->fd_in) == -1)
			return (1);
	}
	if (data->fd_out != 0)
	{
		if (dup2(STDOUT_FILENO, data->fd_out) == -1)
			return (1);
	}
	return (0);
}

executing(t_all *all)
{
	int	builtin;

	while (all->first->next)
	{
		if (fd_handle(all->first))
			return (exit(all));

	}
}

int main()
{
	char	*str = ft_strdup("pwd");
	printf("%d", is_builtin(str));
}