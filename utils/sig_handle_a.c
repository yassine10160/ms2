/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:49:05 by dmazari           #+#    #+#             */
/*   Updated: 2025/05/21 14:48:56 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_handler(void)
{
	struct sigaction	s;

	sigemptyset(&s.sa_mask);
	s.sa_handler = here_doc_sig;
	s.sa_flags = 0;
	sigaction(SIGINT, &s, NULL);
}

void	child_sig(int s)
{
	if (s == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
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
	sigaction(SIGINT, &s, NULL);
}
