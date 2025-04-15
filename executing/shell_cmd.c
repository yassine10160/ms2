/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:24:31 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/04/15 15:56:00 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	shell_cmd(t_all *all)
{
	char	**cmds;
	char	**env;
	char	*path_cmd;

	cmds = cmds_to_strs(all->first->cmds, 1, 0);
	if (!cmds)
		ft_exit(all, NULL);
	env = env_to_strs(all->env, 0, 1);
	if (!env)
	{
		free_strs(cmds);
		ft_exit(all, NULL);
	}
	path_cmd = get_path_cmd(cmds[0], get_path_env(all->env));
	if (!path_cmd)
	{
		free_strs(env);
		free_strs(cmds);
		// return (print_error(cmds[0], "command not found"));
	}
	return (0);
}

// int main(int ac, char **av, char **env)
// {
// 	t_all *all = init_all(env);
// 	char	*str = ft_strdup("cd");
	
// 	(void)ac;
// 	(void)av;
// 	all->first->cmds->token = str;
// 	shell_cmd(all);
// }

// t_data *save;
// t_cmds *tmp;

// save = all->first;
// while (all->first)
// {
// 	tmp = all->first->cmds;
// 	while (all->first->cmds)
// 	{
// 		printf("%s", all->first->cmds->token);
// 		all->first->cmds = all->first->cmds->next;
// 	}
// 	all->first->cmds = tmp;
// 	all->first = all->first->next;
// }
// all->first = save;