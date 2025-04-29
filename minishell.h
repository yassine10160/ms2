/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:14:10 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/29 14:23:59 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#define INFILE 1
#define OUTFILE 2
#define PIPE 3
#define NONE 4
#define APPEND 5

typedef enum e_builtin
{
	EXPORT = 1,
	ECHO,
	EXIT,
	UNSET,
	ENV,
	PWD,
	CD,
} t_builtin;

typedef struct s_cmds
{
	char *token;
	struct s_cmds *prev;
	struct s_cmds *next;
} t_cmds;

typedef struct s_env
{
	char *line;
	struct s_env *prev;
	struct s_env *next;
} t_env;

typedef struct s_data
{
	t_cmds *cmds;
	int fd_in;
	int fd_out;
	int pipe_fd[2];
	struct s_data *prev;
	struct s_data *next;
} t_data;

typedef struct s_all
{
	t_data *first;
	t_env *env;
	int status;
	int f_here_doc;
	int *pids;
} t_all;

/*
** builtin/env_functions.c
*/
int ft_strcmp(char *s1, char *s2);
t_env *find_in_env(t_env *env, char *str);

/*
** builtin/env_parsing.c
*/
void *free_new_env(t_env *env);
char *ft_strdup(char *str);
t_env *add_lst(t_env *prev);
t_env *env_to_struct(char **env);

/*
** builtin/ft_cd.c
*/
char *get_pwd(char *prefix);
void put_pwd(t_env *env, char **pwd, int i);
int get_home(t_env *env, char **arg);
int ft_cd(t_env *env, char *arg);

/*
** builtin/ft_echo.c
*/
int is_n(t_cmds *cmd);
void ft_echo(t_cmds *cmd);

/*
** builtin/ft_env.c
*/
void ft_env(t_env *env);

/*
** builtin/ft_exit.c
*/
int ft_atoi(char *str);
void ft_exit(t_all *all, t_cmds *cmd);

/*
** builtin/ft_export.c
*/
int print_export(t_env *env, int i);
int add_lst_str(t_env *prev, char *var);
char *get_var_name(char *str);
void modify_line(t_env *env, char *new_line);
int ft_export(t_env *env, char *new_var);

/*
** builtin/ft_pwd.c
*/
int ft_pwd(void);

/*
** builtin/ft_unset.c
*/
void remove_node(t_env *node);
int ft_unset(t_env *env, t_cmds *cmd);

/*
** executing/builtin_caller.c
*/
int caller_next(t_all *all, int builtin);
int builtin_caller(t_all *all, int builtin);

/*
** executing/executing.c
*/
int is_builtin(char *token);
void executing(t_all *all);

/*
** executing/shell_cmd.c
*/
int shell_cmd(t_all *all);

/*
** executing/get_path.c
*/
char *str_dup_c(char *str, char c_limit, char c_join);
int count_str_c_limit(char *str, char c_limit);
int find_path_string(t_env **env);
char **split_c(char *str, char c_limit, char c_join);
char **get_path_env(t_env *env);

/*
** executing/check_cmd.c
*/
int index_path_cmd(char *cmd, char **path);
char *get_path_cmd(char *cmd, char **path, t_all *all);

/*
** executing/fd_management.c
*/
int setup_input_redirection(t_all *all);
int setup_output_redirection(t_all *all);
int setup_redirections(t_all *all);
int reset_std_descriptors(void);

/*
** executing/cmd_status.c
*/
int extract_exit_status(int wait_status);
void wait_for_processes(t_all *all, int *pids, int cmd_count);
int *init_pids_array(int cmd_count);

/*
** utils/char.c
*/
int is_alpha(char c);
int is_digit(char c);
int is_alphanum(char c);
void is_in_quote(char c, int *sq, int *dq);
int pos_in_str(char *str, char c);

/*
** utils/char_utils2.c
*/
void is_in_sq(char c, int *sq);
void *free_strs(char **strs);

/*
** utils/free_functions.c
*/
void free_env(t_env *env);
void free_cmds(t_cmds *cmds);
void free_data(t_data *data);
void free_all(t_all *all);
void free_new_line(t_all *all);

/*
** utils/strcpy.c
*/
size_t ft_strlen(char *line);
char *ft_strcat(char *str_a, char *str_b, int flag, int i);
char *ft_strndup(char *str, int n);
char **env_to_strs(t_env *env, int i, int count);
char **cmds_to_strs(t_cmds *cmds, int count, int i);

/*
** utils/ft_calloc.c
*/
void *ft_calloc(size_t nmemb, size_t size);

/*
** utils/ft_itoa.c
*/
int len_nb(int nb);
char *ft_itoa(int nb);

/*
**
*/
int is_outfile(char *s);
int is_here_doc(char *s);
int	is_append(char *s);
int is_infile(char *s);

/*
** parsing/init.c
*/
t_data *init_data(int mode);
t_all *init_all(char **env);
t_cmds *add_next_cmds(t_cmds *current);
t_data *add_next_data(t_data *current);
t_cmds *remove_cmd(t_cmds *current);

/*
** parsing/expand.c
*/
int should_expand(char *line, int i, int sq);
char *expand_status(char *line, int status);
int find_var_end(char *line, int i, int *sq, int *dq);
char *search_var_in_env(char *line, char *var, int end_var, t_all *all);
char *expand_var(char *line, t_all *all, int i, int j);

/*
** parsing/expand_null.c
*/
char *expand_null(char *line, int flag, int i);

/*
** parsing/expand_var.c
*/
char *expand_line_var(char *line, char *var_value, int i_var, int sq);

/*
** parsing/split_quote_and_space.c
*/
int word_len(char *str);
char *str_dup_minishell(char *s, int *i, int k, int j);
int split_quote_and_space(char *str, t_all *all);

/*
** parsing/split_pipe.c
*/
void free_str_tab(char **tab, int limit);
int calc_nb_words(char const *s, char *delim);
char *fill_word(char *word, char const *s, int start, int end);
int alloc_n_write(char **res, char const *s, char *delim);
char **split_pipe(char const *s, char *delim);

/*
** parsing/add_space.c
*/
int count_space(char *line);
char *add_space(char *line);

/*
** parsing/handle_line.c
*/
void handle_line(t_all **all, char *line);

/*
** main.c
*/
void new_line(t_all *all);
void exit_parse(char *line, char *s, t_all *all, int status);
int is_parse_err(char c);
int parse_error(char *str, t_all *all);
int is_closed(char *line);

#endif