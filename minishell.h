/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:20:41 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 13:20:55 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdlib.h>

typedef struct s_cmds
{
	char			*cmd;
	struct s_cmds	*prev;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_env
{
	char			*line;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_data

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2)
		return (0);
	while (s1 && s2 && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (2);
	if (!s2[i])
		return (1);
	return (0);
}

t_env	*find_in_env(t_env *env, char *str)
{
	t_env	*save;

	save = env;
	while (save->prev)
		save = save->prev;
	while (save->next)
	{
		if (ft_strcmp(save->line, str))
			return (save);
		save = save->next;
	}
	return (NULL);
}
	cmds;
	int				fd_in;
	int				fd_out;
	int				pipe_fd[2];
	struct s_data	*prev;
	struct s_data	*next;
}	t_data;

typedef struct s_all
{
	t_data	*first;
	t_env	*env;
	int		status;
}	t_all;

#endif