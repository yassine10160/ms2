/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:31:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/12 14:23:20 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		put_str_fd("getcwd : no working directory\n", 2);
	else
		printf("%s\n", pwd);
	if (!pwd)
		return (1);
	if (pwd)
		free(pwd);
	return (0);
}
