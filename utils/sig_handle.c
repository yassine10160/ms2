/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:07:12 by yafahfou          #+#    #+#             */
/*   Updated: 2025/05/18 14:31:37 by mazakov          ###   ########.fr       */
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
	signal(SIGQUIT, SIG_IGN);
	s.sa_handler = parent_sig;
	s.sa_flags = 0;
	sigaction(SIGINT, &s, NULL);
}

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
		write(1, "\n", 1);
		g_stop = 2;
	}
}

void	child_handler(void)
{
	struct sigaction	s;

	sigemptyset(&s.sa_mask);
	s.sa_handler = child_sig;
	s.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &s, NULL);
	sigaction(SIGINT, &s, NULL);
}
