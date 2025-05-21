/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:49:05 by dmazari           #+#    #+#             */
/*   Updated: 2025/05/21 12:49:17 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_handler(void)
{
	struct sigaction	s;

	sigemptyset(&s.sa_mask);
	signal(SIGQUIT, SIG_IGN);
	s.sa_handler = here_doc_sig;
	s.sa_flags = 0;
	sigaction(SIGINT, &s, NULL);
}

void	child_sig(int s)
{
	if (s == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		rl_redisplay();
		g_stop = 3;
	}
	if (s == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		g_stop = 2;
	}
}

void	child_handler(int back)
{
	struct sigaction	s;

	sigemptyset(&s.sa_mask);
	s.sa_handler = child_sig;
	s.sa_flags = SA_RESTART;
	if (back)
		sigaction(SIGQUIT, &s, NULL);
	else
		signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &s, NULL);
}
