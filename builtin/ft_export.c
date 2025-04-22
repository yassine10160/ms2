/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:26:08 by mazakov           #+#    #+#             */
/*   Updated: 2025/04/22 15:15:30 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export(t_env *env, int i)
{
	int	q;

	while (env->prev)
		env = env->prev;
	while (env->next)
	{
		printf("export ");
		i = 0;
		q = 0;
		while (env->line[i])
		{
			if ((i > 0) && (env->line[i - 1] == '='))
			{
				printf("\"");
				q++;
			}
			printf("%c", env->line[i]);
			i++;
		}
		if (q == 1)
			printf("\"");
		printf("\n");
		env = env->next;
	}
	return (0);
}

int	add_lst_str(t_env *prev, char *var)
{
	t_env	*new_node;
	t_env	*ptr;

	if (!prev->prev && !prev->next && !prev->line)
	{
		prev->line = var;
		ptr = add_lst(prev);
		if (!ptr)
			return (2);
		return (0);
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->prev = prev;
	new_node->next = prev->next;
	prev->next = new_node;
	new_node->line = var;
	return (0);
}

char	*get_var_name(char *str)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	var = malloc(sizeof(char) * (i + 2));
	if (!var)
		return (NULL);
	while (j <= i)
	{
		var[j] = str[j];
		j++;
	}
	var[j] = 0;
	return (var);
}

void	modify_line(t_env *env, char *new_line)
{
	char	*save;

	save = env->line;
	free(save);
	env->line = new_line;
}

int	ft_export(t_env *env, char *new_var)
{
	char	*var_name;
	t_env	*save;

	if (!new_var)
		return (print_export(env, 0));
	var_name = get_var_name(new_var);
	if (!var_name)
		return (1);
	if (is_alpha(var_name[0]) != 1)
	{
		printf("export: '%s': not a valid identifier\n", var_name);
		free(var_name);
		return (2);
	}
	save = find_in_env(env, var_name);
	free(var_name);
	if (!save)
	{
		if (add_lst_str(env, new_var) == 1)
			return (1);
	}
	else
		modify_line(save, new_var);
	return (0);
}

// int main(int ac, char **av, char **env)
// {
// 	t_env *menv;
// 	char	*str1 = ft_strdup("a=salut");
// 	char	*str2 = ft_strdup("b=coucou");
// 	char	*str3 = ft_strdup("a=coucou");
// 	menv = env_to_struct(env);

// 	ft_export(menv, str1);
// 	ft_export(menv, str2);
// 	ft_export(menv, str3);
// 	ft_env(menv);
// 	ft_export(menv, NULL);
// 	free_new_env(menv);
// }
