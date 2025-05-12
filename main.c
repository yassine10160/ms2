/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:08:05 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/05/12 19:04:56 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_all	*all;
	char	*line;

	(void)ac;
	(void)av;
	all = init_all(env);
	while (1)
	{
		line = readline("Schwarzenegger : ");
		if (line)
		{
			add_history(line);
			process_line(line, all);
		}
		else
		{
			free(line);
			ft_exit(all, NULL);
		}
	}
}
