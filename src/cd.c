/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:29:22 by alexis            #+#    #+#             */
/*   Updated: 2024/10/11 14:14:42 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chdir_error(char *oldpwd, char *value)
{
	if (errno == 20)
		ft_printf("bash: cd: %s: Not a directory\n", value);
	if (errno == 2)
		ft_printf("bash: cd: %s: No such file or directory\n", value);
	free(oldpwd);
	global_variable(1, 0);
}

// ft_printf("errno = %i\n", global_variable(0, 1));

int	check_arg_cd(char **value, t_env **env)
{
	int		i;
	char	*oldpwd;

	i = 0;
	while (value[i])
		i++;
	if (i > 2)
	{
		ft_printf("bash: cd: too many arguments\n");
		global_variable(1, 0);
		return (0);
	}
	if (i == 2)
	{
		oldpwd = getcwd(NULL, 0);
		i = chdir(value[1]);
		if (i != 0)
			return (chdir_error(oldpwd, value[1]), 1);
		set_old_pwd(*env, oldpwd);
		set_pwd(*env);
		free(oldpwd);
	}
	return (0);
}

int	check_exception_cd(char *value, t_env *env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (cd_tiret(value, env, oldpwd) == 1)
	{
		free(oldpwd);
		return (0);
	}
	if (cd_all(value, env, oldpwd) == 1)
	{
		free(oldpwd);
		return (0);
	}
	free(oldpwd);
	return (1);
}

int	ft_cd(char **value, t_env **env)
{
	char	*path;

	if (!(value[1]))
	{
		path = getcwd(NULL, 0);
		set_old_pwd(*env, path);
		free(path);
		if (chdir(search_in_ev("HOME", *env)) != 0)
			home_not_set(*env, NULL);
		set_pwd(*env);
	}
	if (value[1])
	{
		if (check_exception_cd(value[1], *env) == 0)
			return (0);
		check_arg_cd(value, env);
	}
	return (0);
}
