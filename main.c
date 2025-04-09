/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:08:05 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/09 14:12:28 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_error(char *str)
{
	int i;
	int sq;
	int dq;
	int trigger;

	i = 0;
	sq = 0;
	dq = 0;
	trigger = 0;
	while (str && str[i])
	{
		is_in_quote(str[i], &sq, &dq);
		if ((str[i] == '<' || str[i] == '>') && !(sq % 2) && !(dq % 2))
		{
			if (str[i + 1] = ' ')
				trigger = 1;
		}
		if ()
	}
}

int main()
{
	t_all all;
	char *line;

	while (1)
	{
		line = readline(NULL);
		parse_error(line);
	}
}
