/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/29 17:58:14 by acoste           ###   ########.fr       */
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
		if (p->value)
			free(p->value);
		free(p);
		p = tmp;
	}
}

int	get_idx(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i);
}

char	**constructor(char *s)
{
	char	**build;
	int		flag;

	build = malloc(sizeof(char *) * 3);
	flag = get_idx(s, '=');
	build[0] = word_dup(s, 0, flag);
	build[1] = word_dup(s, (flag + 1), ft_strlen(s));
	return (build);
}


void	init_env(t_env **env, char **ev)
{
	char	**cpy_env;
	char	**tmp;

	cpy_env = ev;
	while (*cpy_env)
	{
		tmp = constructor(*cpy_env);
		ft_lstadd_back(env, ft_lstnew(tmp[0], tmp[1]));
		if(tmp[0])
			ft_free_split(tmp);
		cpy_env++;
	}
}
