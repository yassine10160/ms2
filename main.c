/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:08:05 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/05/19 16:54:47 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stop = 0;

int	main(int ac, char **av, char **env)
{
	t_all	*all;
	char	*line;

	if (ac > 1)
	{
		write(2, "Too many arguments\n", 20);
		return (0);
	}
	(void)av;
	all = init_all(env);
	while (1)
	{
		parent_handler();
		line = readline("Schwarzenegger$ ");
		if (g_stop == 2)
			all->status = 130;
		if (g_stop == 3)
			all->status = 131;
		if (line)
		{
			add_history(line);
			process_line(line, all);
		}
		else
			ft_exit(all, NULL);
	}
}
