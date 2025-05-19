/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:16:22 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/19 22:57:01 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safe_open(t_data *data, char *file, int type)
{
	if (data->fd_out == -1)
		return ;
	if (type == INFILE)
	{
		data->fd_in = open(file, O_RDONLY);
		if (data->fd_in == -1)
			put_str_error(file, "No such file or directory", 2);
	}
	else if (type == OUTFILE)
	{
		data->fd_out = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (data->fd_out == -1)
			put_str_error(file, "Permission denied", 2);
	}
	else if (type == HERE_DOC)
	{
		data->fd_in = open(file, O_RDONLY);
		if (data->fd_in == -1)
			put_str_fd("here_doc: Error\n", 2);
	}
	else
	{
		data->fd_out = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (data->fd_out == -1)
			put_str_error(file, "Permission denied", 2);
	}
}

void	handle_redirection(t_cmds **tmp, t_data *data, int fd)
{
	if (is_infile((*tmp)->token))
	{
		if (is_here_doc((*tmp)->token) == -1)
			safe_open(data, (*tmp)->next->token, INFILE);
		else if (fd != -2)
			safe_open(data, ".tmp", HERE_DOC);
		*tmp = remove_cmd(*tmp);
		*tmp = remove_cmd(*tmp);
		data->cmds = *tmp;
	}
	else if (is_outfile((*tmp)->token))
	{
		if (is_append((*tmp)->token))
			safe_open(data, (*tmp)->next->token, APPEND);
		else
			safe_open(data, (*tmp)->next->token, OUTFILE);
		*tmp = remove_cmd(*tmp);
		if (*tmp)
			*tmp = remove_cmd(*tmp);
		data->cmds = *tmp;
	}
}

int	process_lines(char **s, t_all *all, int i)
{
	char	*buf;

	while (s && s[i])
	{
		buf = expand_var(s[i], all);
		if (!buf)
		{
			free_strs(s);
			ft_exit(all, NULL);
		}
		s[i++] = buf;
	}
	return (i);
}
