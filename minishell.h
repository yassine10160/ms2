/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:20:41 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 10:48:52 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
{
	char			*line;
	t_cmds			cmds;
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