/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:29:22 by alexis            #+#    #+#             */
/*   Updated: 2024/10/09 19:50:49 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *search_in_ev(char *value, t_env *env)
{
	t_env *tmp;
	char *temp;

	tmp = env;
	while (env)
	{
		if (!ft_cmp(value, env->key))
		{
			temp = env->value;
			env = tmp;
			return(temp);
		}
		env = env->next;
	}
	env = tmp;
	return (0);
}

int	check_arg_cd(char **value, t_env **env)
{
	int i;
	char *oldpwd;

	i = 0;
	while (value[i])
		i++;
	if (i > 2)
	{
		ft_printf("bash: cd: too many arguments");
		return (0);
	}
	if (i == 1)
	{
		oldpwd = getcwd(NULL, 0);
		printf("value[1] = %s\n", value[1]);
		if (chdir(value[1]) != 0)
		{
			ft_printf("bash: cd: %s: No such file or directory", value[1]);
			return (1);
		}
		set_old_pwd(*env, oldpwd);
		set_pwd(*env);
	}
	return (0);
}

int	ft_cd(char **value, t_env **env)
{
	char *path;
	if (!(value[1]))
	{
		path = search_in_ev("HOME", *env);
		printf("path = %s\n", path);
		chdir(path);
	}
	if (value[1])
	{
		if (check_exception_cd(value[1], *env) == 0)
			return (0);
		if (check_arg_cd(value, env) == 0)
			return (0);
	}
	if (chdir(search_in_ev("HOME", *env)) != 0)
		ft_printf("bash: cd: HOME not set");
	return (0);
}

int	check_exception_cd(char *value, t_env *env)
{
	char *oldpwd;

	oldpwd = getcwd(NULL, 0);
	if ((value[0] == '-') && (!(value[1])))
	{
		if (chdir(search_in_ev("HOME", env)) != 0)
		{
			ft_printf("bash: cd: HOME not set");
			return (1);
		}
	}
	if ((value[0] == '-') && (value[1] == '-') && (!(value[2])))
	{
		if (chdir(search_in_ev("HOME", env)) != 0)
		{
			ft_printf("bash: cd: HOME not set");
			return (0);
		}
	}
	set_old_pwd(env, oldpwd);
	set_pwd(env);
	return (0);
}
