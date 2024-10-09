/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:57:16 by alexis            #+#    #+#             */
/*   Updated: 2024/10/09 22:40:10 by alexis           ###   ########.fr       */
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
	int i;

	i = 0;
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
			printf("new pwd modif too : %s\n", pwd);
			printf("\n\n%i\n\n", i);
		}
		env = env->next;
		i++;
	}
	env = tmp;
}

void	set_old_pwd(t_env *env, char *path)
{
	t_env	*tmp;
	char *old_pwd;

	tmp = env;
	if (!path)
		old_pwd = getcwd(NULL, 0);
	else
		old_pwd = ft_strdup(path);
	while(env)
	{
		if(!(ft_strncmp(env->key, "OLDPWD", 7)))
		{
			free(env->value);
			env->value = old_pwd;
			printf("oldpwd modif too : %s\n", old_pwd);
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