/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/24 21:26:08 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env	*p)
{
	t_env	*tmp;

	while (p)
	{
		tmp = p->next;
		free(p->key);
		free(p->value);
		free(p);
		p = tmp;
	}
}

void	init_env(t_env **env, char **ev)
{
	char	**cpy_env;
	char	**tmp;

	cpy_env = ev;
	while (*cpy_env)
	{
		tmp = ft_split(*cpy_env, '=');
		ft_lstadd_back(env, ft_lstnew(tmp[0], tmp[1]));
		ft_free_split(tmp);
		cpy_env++;
	}
	display_env(env); //new
}

void	display_env(t_env **env) //new
{
	if (env[0] == NULL)
	{
		write (2, "env: ", 5);
// ?		ft_putstr()
		write (2, "No such file or directory\n)", 28);
	}
	while((*env)->next)
	{
		ft_putstr((*env)->key);
		if ((*env)->value)
		{
			ft_putstr("=");
			ft_putstr((*env)->value);
		}
		write(1, "\n", 1);
		(*env) = (*env)->next;
	}
	ft_putstr((*env)->key);
	if ((*env)->value)
	{
		ft_putstr("=");
		ft_putstr((*env)->value);
	}
	write(1, "\n", 1);
}