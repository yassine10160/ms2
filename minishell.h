/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:50:29 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/12 14:17:42 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>

# define INFILE 1
# define OUTFILE 2
# define PIPE 3
# define NONE 4
# define APPEND 5

# define BUFFER_SIZE 1000

typedef enum e_builtin
{
	EXPORT = 1,
	ECHO,
	EXIT,
	UNSET,
	ENV,
	PWD,
	CD,
}	t_builtin;

typedef struct s_cmds
{
	char			*token;
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
	int				pipe_fd[2];
	int				fd_in;
	int				fd_out;
	struct s_data	*prev;
	struct s_data	*next;
}	t_data;

typedef struct s_all
{
	t_data			*first;
	t_env			*env;
	int				*pids;
	int				fd_save[2];
	int				f_here_doc;
	int				status;
	int				g_pid;
}	t_all;
/*
** main.c
*/
int		process_line(char *line, t_all *all);

/*
** builtin/env_functions.c
*/
int		ft_strcmp(char *s1, char *s2);
t_env	*find_in_env(t_env *env, char *str);

/*
** builtin/export_utils.c
*/
int		add_lst_str(t_env *prev, char *var);
char	*get_var_name(char *str);
int		modify_line(t_env *env, char *new_line);
int		is_valid_identifier(char *var_name, char *token);

/*
** builtin/env_parsing.c
*/
void	*free_new_env(t_env *env);
char	*ft_strdup(char *str);
t_env	*add_lst(t_env *prev);
t_env	*env_to_struct(char **env);

/*
** builtin/ft_cd.c
*/
char	*get_pwd(char *prefix);
void	put_pwd(t_env *env, char **pwd, int i);
int		get_home(t_env *env, char **arg);
int		ft_cd(t_env *env, char *arg);

/*
** builtin/ft_echo.c
*/
int		is_n(t_cmds *cmd);
void	ft_echo(t_cmds *cmd);

/*
** builtin/ft_env.c
*/
int		is_printable(char *str);
void	ft_env(t_env *env);

/*
** builtin/ft_exit.c
*/
int		ft_atoi(char *str);
void	ft_exit(t_all *all, t_cmds *cmd);

/*
** builtin/ft_export.c
*/
int		print_export(t_env *env, int i);
int		ft_export(t_env *env, t_cmds *cmds);

/*
** builtin/ft_pwd.c
*/
int		ft_pwd(void);

/*
** builtin/ft_unset.c
*/
void	remove_node(t_env *node);
int		ft_unset(t_env *env, t_cmds *cmd);

/*
** executing/builtin_caller.c
*/
int		caller_next(t_all *all, int builtin);
int		builtin_caller(t_all *all, int builtin);

/*
** executing/check_cmd.c
*/
int		index_path_cmd(char *cmd, char **path);
int		check_local(char *cmd, char **path_cmd);
char	*get_path_cmd(char *cmd, char **path, t_all *all);

/*
** executing/cmd_status.c
*/
int		extract_exit_status(int wait_status);
void	wait_for_processes(t_all *all, int *pids, int cmd_count);
int		*init_pids_array(int cmd_count);

/*
** executing/executing.c
*/
int		is_builtin(char *token);
int		count_cmds(t_all *all);
int		builtin_child(t_all *all, int builtin);
void	execute_cmd(t_all *all, int *pids, int i);
void	executing(t_all *all, int i);

/*
** executing/fd_management.c
*/
int		setup_input_redirection(t_all *all);
int		setup_output_redirection(t_all *all);
int		setup_redirections(t_all *all, int *fd_save_in, int *fd_save_out);
void	close_init_fd(int *fd_in, int *fd_out);
int		reset_std_descriptors(int *fd_save_in, int *fd_save_out);

/*
** executing/handle_input.c
*/
void	write_error(char *line, char *s, t_all *all, int status);
int		parse_err(char c);
int		parse_error(char *s, t_all *all);
int		is_closed(char *line);
int		process_line(char *line, t_all *all);

/*
** executing/get_path.c
*/
char	*str_dup_c(char *str, char c_limit, char c_join);
int		count_str_c_limit(char *str, char c_limit);
int		find_path_string(t_env **env);
char	**split_c(char *str, char c_limit, char c_join);
char	**get_path_env(t_env *env);

/*
** executing/shell_cmd.c
*/
int		execute_in_child(char **cmds, char **env, char *path_cmd);
void	clean_resources(char **cmds, char **env, char *path_cmd);
int		handle_fork_error(char **cmds, char **env, char *path_cmd, t_all *all);
int		prepare_execution(t_all *all, char ***cmd, char ***env, char **path_c);
int		shell_cmd(t_all *all);

/*
** parsing/add_space.c
*/
int		count_space(char *line);
char	*add_space(char *line);

/*
** parsing/expand.c
*/
int		should_expand(char *line, int i, int sq);
char	*expand_status(char *line, int status);
int		find_var_end(char *line, int i, int *sq, int *dq);
char	*search_var_in_env(char *line, char *var, int end_var, t_all *all);
char	*expand_var(char *line, t_all *all);

/*
** parsing/expand_null.c
*/
void	init_expand_vars(int *sq, int *dq, char **dup, char *line);
int		skip_var(char *line, int i, int *sq, int *dq);
char	*expand_null(char *line, int flag, int i);

/*
** parsing/expand_var.c
*/
int		find_var_start(char *var_value, int i, int *j, int *k);
char	*alloc_expanded_str(char *line, char *var_value, int i_var);
int		copy_var(char *var_value, char *s, int i_var, int i_s);
int		handle_dollar(char *line, int i, int *sq, int *dq);
char	*expand_line_var(char *line, char *var_value, int i_var, int sq);

/*
** parsing/handle_line.c
*/
char	**handle_space(t_all *all, char *line, int *fd);
int		set_line(t_all *all, char *line, int i, int fd);
void	handle_all(t_all *all, int fd);
void	handle_line(t_all **all, char *line);

/*
** parsing/handle_line_utils.c
*/
void	safe_open(t_all *all, t_data *data, char *file, int type);
void	handle_redirection(t_all *all, t_cmds **tmp, t_data *data, int fd);
int		process_lines(char **s, t_all *all, int i);

/*
** parsing/init.c
*/
t_data	*init_data(void);
t_all	*init_all(char **env);
t_cmds	*add_next_cmds(t_cmds *current);
t_data	*add_next_data(t_data *current);
t_cmds	*remove_cmd(t_cmds *current);

/*
** parsing/redir_utils.c
*/
int		is_outfile(char *s);
int		is_here_doc(char *s);
int		is_append(char *s);
int		is_infile(char *s);
bool	is_quote_delim(char *s, int index);

/*
** parsing/redir.c
*/
int		len_delim(char *s, int start);
char	*get_delim(char *s, int index, int len);
void	write_and_expand_file(t_all *all, int fd, char *line, bool is_quote);
int		handle_here_doc(t_all *all, char *delim, bool is_quote);
int		check_here_doc(t_all *all, char *s);

/*
** parsing/split_pipe.c
*/
void	free_str_tab(char **tab, int limit);
int		calc_nb_words(char const *s, char *delim);
char	*fill_word(char *word, char const *s, int start, int end);
int		alloc_n_write(char **res, char const *s, char *delim, int i);
char	**split_pipe(char const *s, char *delim);

/*
** parsing/split_quote_and_space.c
*/
int		word_len(char *str);
char	*str_dup_minishell(char *s, int *i, int k, int j);
int		split_quote_and_space(char *str, t_all *all);

/*
** utils/char.c
*/
int		is_alpha(char c);
int		is_digit(char c);
int		is_alphanum(char c);
void	is_in_quote(char c, int *sq, int *dq);
int		pos_in_str(char *str, char c);

/*
** utils/put_str.c
*/
void	put_str_fd(char *str, int fd);
void	put_str_error(char *cmd, char *str, int fd);
void	put_str_function(char *function, char *cmd, char *str, int fd);

/*
** utils/char_utils2.c
*/
void	is_in_sq(char c, int *sq);
void	*free_strs(char **strs);

/*
** utils/free_functions.c
*/
void	free_env(t_env *env);
void	free_cmds(t_cmds *cmds);
void	free_data(t_data *data);
void	free_all(t_all *all);
void	free_new_line(t_all *all);

/*
** utils/ft_calloc.c
*/
void	*ft_calloc(size_t nmemb, size_t size);

/*
** utils/ft_itoa.c
*/
int		len_nb(int nb);
char	*ft_itoa(int nb);

/*
** utils/get_next_line.c
*/
char	*ft_strjoin_check(char *s1, char *s2);
int		read_file(char *buff, char **str, int fd);
char	*get_next_line(int fd);

/*
** utils/get_next_line_utils.c
*/
char	*ft_strjoin_gnl(char const *s1, char const *s2, int index);
int		ft_index_line(char *s);
void	ft_reset(char *s, int stop);

/*
** utils/strcpy.c
*/
size_t	ft_strlen(char *line);
char	*ft_strcat(char *str_a, char *str_b, int flag, int i);
char	*ft_strndup(char *str, int n);
char	**env_to_strs(t_env *env, int i, int count);
char	**cmds_to_strs(t_cmds *cmds, int count, int i);
int		ft_strncmp(const char *s1, const char *s2, int n);

#endif