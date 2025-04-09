/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:54 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 13:23:41 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_n(char *flag)
{
	int	i;

	i = 0;
	if (flag && flag[0] == '-')
	{
		i++;
		if (!flag[i])
			return (0);
		while (flag[i] && flag[i] == 'n')
			i++;
		if (!flag[i])
			return (1);
	}
	return (0);
}

void	ft_echo(char **str)
{
	int	i;
	int	flag;

	flag = is_n(str[0]);
	if (!str && !flag)
		printf("\n");
	if (!str)
		return ;
	i = 0;
	if (flag)
		i++;
	while (str && str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}
int	is_n(char *flag)
{
	int	i;

	i = 0;
	if (flag && flag[0] == '-')
	{
		i++;
		if (!flag[i])
			return (0);
		while (flag[i] && flag[i] == 'n')
			i++;
		if (!flag[i])
			return (1);
	}
	return (0);
}

void	ft_echo(char **str)
{
	int	i;
	int	flag;

	flag = is_n(str[0]);
	if (!str && !flag)
		printf("\n");
	if (!str)
		return ;
	i = 0;
	if (flag)
		i++;
	while (str && str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}
