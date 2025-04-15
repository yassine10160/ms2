/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:46:31 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/15 13:24:53 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void is_in_sq(char c, int *sq)
{
	if (c == '\'')
		*sq = *sq + 1;
}

void	*free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
	if (strs)
		free(strs);
	return (NULL);
}
