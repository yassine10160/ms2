/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:01:07 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/12 14:28:50 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_str_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

void	put_str_error(char *cmd, char *str, int fd)
{
	if (cmd)
	{
		put_str_fd(cmd, fd);
		put_str_fd(" : ", fd);
	}
	if (str)
	{
		put_str_fd(str, fd);
		put_str_fd("\n", fd);
	}
}

void	put_str_function(char *function, char *cmd, char *str, int fd)
{
	if (function)
	{
		put_str_fd(function, fd);
		put_str_fd(": '", fd);
	}
	if (cmd)
		put_str_fd(cmd, fd);
	if (function)
		put_str_fd("' : ", fd);
	if (str)
	{
		put_str_fd(str, fd);
		put_str_fd("\n", fd);
	}
}
