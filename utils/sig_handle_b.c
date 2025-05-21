/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:07:12 by yafahfou          #+#    #+#             */
/*   Updated: 2025/05/21 14:49:10 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_sig(int s)
{
	if (s == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_stop = 2;
	}
}

void	here_doc_sig(int s)
{
	if (s == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		g_stop = 2;
	}
}

void	parent_handler(void)
{
	struct sigaction	s;

	g_stop = 0;
	sigemptyset(&s.sa_mask);
	s.sa_handler = parent_sig;
	s.sa_flags = 0;
	sigaction(SIGINT, &s, NULL);
}
