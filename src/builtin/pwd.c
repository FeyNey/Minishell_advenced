/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:57:16 by alexis            #+#    #+#             */
/*   Updated: 2024/10/09 20:07:02 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str)
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	set_pwd(t_env *env)
{
	t_env	*tmp;
	char *pwd;

	tmp = env;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr("pwd_error");
		return ;
	}
	while (env)
	{
		if (!(ft_strncmp(env->key, "PWD", 3)))
		{
			free(env->value);
			env->value = pwd;
		}
		env = env->next;
	}
	env = tmp;
}

void	set_old_pwd(t_env *env, char *path)
{
	t_env	*tmp;
	char *old_pwd;

	tmp = env;
	// est ce que path sera malloc ??
	if (!path)
		old_pwd = getcwd(NULL, 0);
	else
		old_pwd = ft_strdup(path);
	// est ce que path sera malloc ??
	while(env)
	{
		if(!(ft_strncmp(env->key, "OLD_PWD", 7)))
		{
			free(env->value);
			env->value = old_pwd;
		}
		env = env->next;
	}
	env = tmp;
}

int	ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		ft_putstr("error pwd");
		return (-1);
	}
	return(0);
}