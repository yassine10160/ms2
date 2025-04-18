/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:08:05 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/15 18:02:46 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

// Only declare functions that are definitely available
extern int rl_on_new_line(void);
extern void rl_redisplay(void);

// Global flag to indicate SIGINT was received
volatile sig_atomic_t g_sigint_received = 0;

// Global to store a reference to the current shell state
t_all *g_shell = NULL;

void	sigint_handler(int sig)
{
	(void)sig;
	// Set the flag that SIGINT was received
	g_sigint_received = 1;
	// Print a newline to reset the prompt
	write(STDOUT_FILENO, "\n", 1);
	// Force readline to update its internal state
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	
	// Ignore SIGQUIT (Ctrl+\)
	signal(SIGQUIT, SIG_IGN);
}

void	new_line(t_all *all)
{
	free_data(all->first);
	all->first = init_data();
	if (!all->first)
		ft_exit(all, NULL);
}

void exit_parse(char *s, t_all *all, int status)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	all->status = status;
}

int is_parse_err(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int parse_error(char *str, t_all *all)
{
	int i;
	int sq;
	int dq;

	i = -1;
	sq = 0;
	dq = 0;
	while (str && str[++i])
	{
		is_in_quote(str[i], &sq, &dq);
		if ((is_parse_err(str[i])) && !(sq % 2) && !(dq % 2))
		{
			if (is_parse_err(str[i + 1]) && str[i] == str[i + 1] && str[i] != '|')
				i++;
			i++;
			while (str[i] == ' ')
				i++;
			if ((is_parse_err(str[i]) || str[i] == '\0'))
			{
				exit_parse("parsing error", all, 258);
				return (1);
			}
		}
	}
	return (0);
}

int is_closed(char *line)
{
	int i;
	int sq;
	int dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (line && line[i])
	{
		is_in_quote(line[i], &sq, &dq);
		i++;
	}
	if ((dq % 2) || (sq % 2))
		return (0);
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_all *all;
	char *line;

	(void)ac;
	(void)av;
	all = init_all(env);
	if (!all)
		return (1);
		
	g_shell = all;
	setup_signals();

	while (1)
	{
		// Reset signal flag before each prompt
		g_sigint_received = 0;
		
		line = readline("minishell$ ");
		if (!line)
		{
			// Handle EOF (Ctrl+D)
			write(STDOUT_FILENO, "exit\n", 5);
			ft_exit(all, NULL);
		}
		
		// Check if we had a SIGINT interrupt
		if (g_sigint_received)
		{
			free(line);
			continue;
		}
		
		if (*line)
		{
			// Add to history only non-empty lines
			add_history(line);
			
			if (!parse_error(line, all))
			{
				if (!is_closed(line))
					exit_parse("error: line not closed", all, 258);
				else
					handle_line(&all, line);
			}
			else
				free(line);
		}
		else
			free(line);
	}
	
	return (0);
}