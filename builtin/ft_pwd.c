/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:31:50 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/02 17:57:34 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		printf("getcwd : no working directory\n");
	else
		printf("%s\n", pwd);
	if (!pwd)
		return (1);
	if (pwd)
		free(pwd);
	return (0);
}
