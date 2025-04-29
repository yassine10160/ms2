/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_and_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:14:56 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/29 14:14:43 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int word_len(char *str)
{
	int i;
	int dq;
	int sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (str && str[i])
	{
		is_in_quote(str[i], &sq, &dq);
		if (!(sq % 2) && !(dq % 2) && str[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

char *str_dup_minishell(char *s, int *i, int k, int j)
{
	char *str;
	int dq;
	int sq;

	str = malloc(sizeof(char) * (word_len(s + *i) + 1));
	if (!str)
		return (NULL);
	dq = 0;
	sq = 0;
	while (s && s[k])
	{
		is_in_quote(s[k], &sq, &dq);
		if ((s[k] == ' ') && !(sq % 2) && !(dq % 2))
			break;
		else if (s[k] == '$' && !is_alpha(s[k + 1]) && (!(sq % 2) && !(dq % 2)))
			k += 2;
		else if ((s[k] == '\'' && ((sq % 2) || (!(dq % 2)))) || (s[k] == '\"' && ((dq % 2) || (!(sq % 2)))))
			k++;
		else
			str[j++] = s[k++];
	}
	*i = k;
	str[j] = '\0';
	return (str);
}

int split_quote_and_space(char *str, t_all *all)
{
	t_cmds *save;
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			all->first->cmds->token = str_dup_minishell(str, &i, i, 0);
			if (!all->first->cmds->token)
				return (1);
			save = add_next_cmds(all->first->cmds);
			if (!save)
				return (1);
			all->first->cmds = save;
		}
	}
	while (all->first->cmds->prev)
		all->first->cmds = all->first->cmds->prev;
	return (0);
}

// int main(int ac, char **av, char **env)
// {
// 	t_all *all;
// 	char *line;

// 	(void)ac;
// 	(void)av;
// 	line = ft_strdup("Salut'la' vie c'est' cool d'etre' la ");
// 	printf("%s\n", line);
// 	all = init_all(env);
// 	if (!all)
// 	{
// 		printf("Error");
// 		return (0);
// 	}
// 	split_minishell(line, all);
// 	while (all->first->cmds->prev)
// 		all->first->cmds = all->first->cmds->prev;
// 	while (all->first->cmds->next)
// 	{
// 		printf("%s\n", all->first->cmds->token);
// 		all->first->cmds = all->first->cmds->next;
// 	}
// 	while (all->first->cmds->prev)
// 		all->first->cmds = all->first->cmds->prev;
// 	free(line);
// 	free_all(all);
// }