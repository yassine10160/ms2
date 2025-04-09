/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:20:41 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 14:16:17 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

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
	t_cmds			*cmds;
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


/*
** builtin/env_functions.c
*/
int				ft_strcmp(char *s1, char *s2);
t_env			*find_in_env(t_env *env, char *str);

/*
** builtin/env_parsing.c
*/
void			*free_new_env(t_env *env);
char			*ft_strdup(char *str);
t_env			*add_lst(t_env *prev);
t_env			*env_to_struct(char **env);

/*
** builtin/ft_cd.c
*/
char			*get_pwd(char *prefix);
void			put_pwd(t_env *env, char **pwd, int i);
int				get_home(t_env *env, char **arg);
int				ft_cd(t_env *env, char *arg);

/*
** builtin/ft_echo.c
*/
int				is_n(char *flag);
void			ft_echo(char **str);

/*
** builtin/ft_env.c
*/
void			ft_env(t_env *env);

/*
** builtin/ft_export.c
*/
int				print_export(t_env *env, int i);
int				add_lst_str(t_env *prev, char *var);
char			*get_var_name(char *str);
void			modify_line(t_env *env, char *new_line);
int				ft_export(t_env *env, char *new_var);

/*
** builtin/ft_pwd.c
*/
int				ft_pwd(void);

/*
** builtin/ft_unset.c
*/
void			remove_node(t_env *node);
int				ft_unset(t_env *env, char *var_name);

/*
** utils/char.c
*/
int				is_alpha(char c);
int				is_digit(char c);
int				is_alphanum(char c);
void			is_in_quote(char c, int *sq, int *dq);

/*
** utils/free_functions.c
*/
void			free_env(t_env *env);
void			free_cmds(t_cmds *cmds);
void			free_data(t_data *data);
void			free_all(t_all *all);

/*
** utils/strcpy.c
*/
size_t			ft_strlen(char *line);
char			*ft_strcat(char *str_a, char *str_b, int flag, int i);
char			*ft_strndup(char *str, int n);

/*
** utils/ft_calloc.c
*/
void *ft_calloc(size_t nmemb, size_t size);

#endif