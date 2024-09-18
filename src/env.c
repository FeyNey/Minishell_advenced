/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/18 15:50:29 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env	*p)
{
	t_env	*next;
	
	while (p)
	{	
		next = p->next;
		free(p->key);
		if (p->value)
			free(p->value);
		free(p);
		p = next;
	}
}
	
char	**constructor(char *s)
{
	char	**build;
	int		flag;

	build = malloc(sizeof(char *) * 3);
	flag = find_c(s, '=');
	build[0] = word_dup(s, 0, flag);
	build[1] = word_dup(s, (flag + 1), ft_strlen(s));
	build[2] = 0;
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
		ft_free_split(tmp);
		cpy_env++;
	}
}
