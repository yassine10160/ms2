/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:20 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/09 13:22:40 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(char *prefix)
{
	size_t	size;
	char	*pwd;
	char	*save;

	pwd = NULL;
	save = NULL;
	size = 0;
	while (!pwd)
	{
		pwd = malloc(sizeof(char) * size);
		if (!pwd)
			return (NULL);
		save = pwd;
		pwd = getcwd(pwd, size);
		if (!pwd)
		{
			free(save);
			size++;
		}
	}
	pwd = ft_strcat(prefix, pwd, 1, 0);
	return (pwd);
}

void	put_pwd(t_env *env, char **pwd, int i)
{
	char	*save;
	t_env	*env_ptr;

	if (i == 2)
		env_ptr = find_in_env(env, "OLDPWD");
	else
		env_ptr = find_in_env(env, "PWD");
	if (!env_ptr)
		add_lst_str(env, *pwd);
	else
	{
		save = env_ptr->line;
		env_ptr->line = *pwd;
		free(save);
	}
}

int	get_home(t_env *env, char **arg)
{
	t_env	*ptr;

	ptr = find_in_env(env, "HOME");
	if (!ptr)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	*arg = ft_strcat(ptr->line + 5, NULL, 0, 0);
	if (!*arg)
		return (2);
	return (0);
}

int	ft_cd(t_env *env, char *arg)
{
	char	*old_pwd;
	char	*new_pwd;

	if (!arg && get_home(env, &arg))
		return (1);
	old_pwd = get_pwd("OLDPWD=");
	if (!old_pwd)
		return (2);
	if (chdir(arg) == -1)
	{
		free(old_pwd);
		printf("cd: %s: No such file or directory\n", arg);
		return (1);
	}
	new_pwd = get_pwd("PWD=");
	if (!new_pwd)
	{
		free(old_pwd);
		return (2);
	}
	put_pwd(env, &new_pwd, 1);
	put_pwd(env, &old_pwd, 2);
	return (0);
}
