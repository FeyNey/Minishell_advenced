/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:10:43 by alexis            #+#    #+#             */
/*   Updated: 2024/10/11 14:14:35 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_ev(char *value, t_env *env)
{
	t_env	*tmp;
	char	*temp;

	tmp = env;
	while (env)
	{
		if (!ft_cmp(value, env->key))
		{
			temp = env->value;
			env = tmp;
			return (temp);
		}
		env = env->next;
	}
	env = tmp;
	return (0);
}

int	swap_pwd_oldpwd(char *pwd, t_env *env)
{
	chdir(search_in_ev("OLDPWD", env));
	set_old_pwd(env, pwd);
	set_pwd(env);
	return (1);
}

int	cd_all(char *value, t_env *env, char *oldpwd)
{
	if (value[0] == '~')
	{
		set_old_pwd(env, oldpwd);
		if (chdir(search_in_ev("HOME", env)) != 0)
			home_not_set(env, NULL);
		set_pwd(env);
		return (1);
	}
	return (0);
}

int	cd_tiret(char *value, t_env *env, char *oldpwd)
{
	if (value[0] == '-')
	{
		if ((value[0] == '-') && (!(value[1])))
		{
			if (chdir(search_in_ev("HOME", env)) != 0)
				home_not_set(env, oldpwd);
			else
				swap_pwd_oldpwd(oldpwd, env);
		}
		else if ((value[0] == '-') && (value[1] == '-') && (!(value[2])))
		{
			if (chdir(search_in_ev("HOME", env)) != 0)
				home_not_set(env, oldpwd);
			else
			{
				set_old_pwd(env, oldpwd);
				chdir(search_in_ev("HOME", env));
				set_pwd(env);
			}
		}
		else
			ft_printf("bash: cd: %s: invalid option\n", value + 1);
		return (1);
	}
	return (0);
}

int	home_not_set(t_env *env, char *oldpwd)
{
	int	i;

	i = 0;
	if (!oldpwd)
	{
		oldpwd = getcwd(NULL, 0);
		i = 1;
	}
	ft_printf("bash: cd: HOME not set\n");
	set_old_pwd(env, oldpwd);
	set_pwd(env);
	if (i == 1)
		free(oldpwd);
	return (1);
}
