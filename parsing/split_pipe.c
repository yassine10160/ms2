/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:45:18 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/29 11:57:50 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_str_tab(char **tab, int limit)
{
	int i;

	i = -1;
	while (++i < limit)
		free(tab[i]);
	free(tab);
}

int calc_nb_words(char const *s, char *delim)
{
	int i;
	int counter;
	int sq;
	int dq;

	sq = 0;
	dq = 0;
	i = 0;
	counter = 0;
	while (s[i])
	{
		is_in_quote(s[i], &sq, &dq);
		if ((pos_in_str(delim, s[i]) == -1) && ((pos_in_str(delim, s[i + 1])) >= 0 || s[i + 1] == '\0') && !(sq % 2) && !(dq % 2))
			counter++;
		i++;
	}
	return (counter);
}

char *fill_word(char *word, char const *s, int start, int end)
{
	int i;

	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

int alloc_n_write(char **res, char const *s, char *delim)
{
	int i;
	int old_i;
	int i_res;
	int sq;
	int dq;

	dq = 0;
	i = 0;
	i_res = 0;
	sq = 0;
	while (s && s[i])
	{
		while (s[i] && (pos_in_str(delim, s[i])) >= 0)
			i++;
		old_i = i;
		while (s[i] && (pos_in_str(delim, s[i]) == -1 || (sq % 2) || (dq % 2)))
			is_in_quote(s[i++], &sq, &dq);
		if (old_i < i)
		{
			res[i_res] = malloc((i - old_i + 1) * sizeof(char));
			if (!res[i_res])
				return (i_res);
			fill_word(res[i_res++], s, old_i, i);
		}
	}
	return (-1);
}

char **split_pipe(char const *s, char *delim)
{
	char **res;
	int nb_words;
	int i_alloc_res;

	if (!s)
		return (NULL);
	nb_words = calc_nb_words(s, delim);
	res = malloc((nb_words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i_alloc_res = alloc_n_write(res, s, delim);
	if (i_alloc_res != -1)
	{
		free_str_tab(res, i_alloc_res);
		return (NULL);
	}
	res[nb_words] = NULL;
	return (res);
}

// int main()
// {
// 	char *s = "ls>a | echo\"|\"";
// 	int i = 0;
// 	char **split;

// 	split = split_pipe(s, "|");
// 	while (s[i])
// 	{
// 		printf("mysplit: %s\n", split[i]);
// 		i++;
// 	}
// 	return (0);
// }