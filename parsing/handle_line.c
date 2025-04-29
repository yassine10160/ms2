/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:27:59 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/04/29 15:43:00 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **handle_space(t_all *all, char *line)
{
	char **s;
	int i;
	char *buf;

	i = 0;
	s = split_pipe(line, "|");
	free(line);
	if (!s)
		ft_exit(all, NULL);
	while (s && s[i])
	{
		buf = add_space(s[i]);
		if (!buf)
		{
			free_strs(s);
			ft_exit(all, NULL);
		}
		free(s[i]);
		s[i++] = buf;
	}
	return (s);
}

void set_line(t_all *all, char *line)
{
	char **s;
	int i;
	char *buf;
	t_data *save;
	t_data *tmp;

	i = 0;
	s = handle_space(all, line);
	while (s && s[i])
	{
		buf = expand_var(s[i], all, 0, 0);
		if (!buf)
		{
			free_strs(s);
			ft_exit(all, NULL);
		}
		s[i++] = buf;
	}
	i = 0;
	save = all->first;
	while (s && s[i])
	{
		if (split_quote_and_space(s[i], all))
		{
			free_strs(s);
			ft_exit(all, NULL);
		}
		if (s[i + 1])
		{
			tmp = add_next_data(all->first);
			all->first = tmp;
			if (!tmp)
			{
				free_strs(s);
				ft_exit(all, NULL);
			}
		}
		i++;
	}
	free_strs(s);
	all->first = save;
}

void safe_open(t_all *all, t_data *data, char *file, int type)
{
	if (type == INFILE)
	{
		data->fd_in = open(file, O_RDONLY);
		if (data->fd_in == -1)
			printf("no such file\n");
		// ft_exit(all, NULL);
	}
	else if (type == OUTFILE)
	{
		data->fd_out = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (data->fd_out == -1)
			ft_exit(all, NULL);
	}
	else
	{
		data->fd_out = open(file, O_WRONLY | O_CREAT, 0777);
		if (data->fd_out == -1)
			ft_exit(all, NULL);
	}
}

int handle_here_doc(t_all *all, t_cmds *cmd)
{
	// all->f_here_doc = open(".tmp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	// if (all->f_here_doc == -1)
	// 	ft_exit(all, NULL);
	// check_delim()
	(void)all;
	(void)cmd;
	return (0);
}

void	handle_all(t_all *all)
{
	t_cmds *tmp;
	t_data *data;

	tmp = all->first->cmds;
	data = all->first;
	while (tmp && data)
	{
		if (is_infile(tmp->token))
		{
			safe_open(all, data, tmp->next->token, INFILE);
			tmp = remove_cmd(tmp);
			tmp = remove_cmd(tmp);
			data->cmds = tmp;
		}
		else if (is_outfile(tmp->token))
		{
			if (is_append(tmp->token))
				safe_open(all, data, tmp->next->token, APPEND);
			else
				safe_open(all, data, tmp->next->token, OUTFILE);
			tmp = remove_cmd(tmp);
			tmp = remove_cmd(tmp);
			data->cmds = tmp;
		}
		else if (is_here_doc(tmp->token))
		{
			handle_here_doc(all, tmp);
			remove_cmd(tmp->next);
			remove_cmd(tmp);
		}
		if (!tmp->next)
		{
			if (data->next)
				data = data->next;
			else
				break;
			tmp = data->cmds;
		}
		else
			tmp = tmp->next;
	}
}

void print_all_data(t_all *all)
{
    t_data *data_curr;
    t_env *env_curr;
    t_cmds *cmds_curr;
    int i;

    if (!all)
    {
        printf("Error: NULL pointer provided\n");
        return;
    }

    // Print general information
    printf("===== ALL STRUCTURE =====\n");
    printf("Status: %d\n", all->status);
    printf("Here_doc flag: %d\n", all->f_here_doc);
    
    // Print process IDs if available
    printf("PIDs: ");
    if (all->pids)
    {
        // We don't know the size of pids array, so we'll check if it's not NULL
        i = 0;
        while (all->pids[i])
        {
            printf("%d ", all->pids[i]);
            i++;
        }
    }
    else
        printf("None");
    printf("\n\n");

    // Print environment variables
    printf("===== ENVIRONMENT VARIABLES =====\n");
    env_curr = all->env;
    while (env_curr)
    {
        printf("ENV: %s\n", env_curr->line ? env_curr->line : "NULL");
        env_curr = env_curr->next;
    }
    printf("\n");

    // Print commands and data structures
    printf("===== COMMANDS AND DATA =====\n");
    data_curr = all->first;
    while (data_curr)
    {
        printf("----- DATA NODE -----\n");
        printf("FD_IN: %d\n", data_curr->fd_in);
        printf("FD_OUT: %d\n", data_curr->fd_out);
        printf("PIPE_FD: [%d, %d]\n", data_curr->pipe_fd[0], data_curr->pipe_fd[1]);
        
        // Print command tokens
        printf("Commands:\n");
        cmds_curr = data_curr->cmds;
        while (cmds_curr)
        {
            printf("  TOKEN: %s\n", cmds_curr->token ? cmds_curr->token : "NULL");
            cmds_curr = cmds_curr->next;
        }
        
        data_curr = data_curr->next;
        printf("\n");
    }
    
    printf("===== END OF DATA =====\n");
}

void handle_line(t_all **all, char *line)
{
	t_data *tmp;

	tmp = (*all)->first;
	set_line(*all, line);
	(*all)->first = tmp;
	handle_all(*all);
	tmp = (*all)->first;
	// print_all_data(*all);
	executing(*all);
	// while (tmp->next)
	// {
	// 	while (tmp->cmds)
	// 	{
	// 		if (tmp->cmds && tmp->cmds->token)
	// 			printf("totok: %s\n", tmp->cmds->token);
	// 		tmp->cmds = tmp->cmds->next;
	// 	}
	// 	printf("fdin: %d\n", tmp->fd_in);
	// 	printf("fdout: %d\n", tmp->fd_out);
	// 	tmp = tmp->next;
	// }
}
