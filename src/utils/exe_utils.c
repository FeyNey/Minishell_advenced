/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:21:36 by aglampor          #+#    #+#             */
/*   Updated: 2024/10/12 19:01:40 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*test_path(char **l_path, char *cmd)
{
	int		i;
	char	*test_path;

	i = 0;
	while (l_path[i])
	{
		test_path = ft_strjoin_t(l_path[i], "/", cmd);
		if (access(test_path, F_OK | X_OK) == 0)
		{
			ft_free_split(l_path);
			return (test_path);
		}
		free(test_path);
		i++;
	}
	ft_free_split(l_path);
	return (0);
}

char	*tru_path(char *ex_cmd, t_env *mev)
{
	char	**list_path;
	char	*path;

	if (ex_cmd[0] == '.' && ex_cmd[1] == '/')
		return (ex_cmd);
	while (mev && ft_cmp("PATH", mev->key))
		mev = mev->next;
	if (!mev)
	{
		global_variable(1, 0); // verif
		return (0);
	}
	list_path = ft_split(mev->value, ':');
	path = test_path(list_path, ex_cmd);
	return (path);
}

char	**get_ex_env(t_env *ev)
{
	t_env	*tmp;
	char	**ex_ev;
	int		i;

	tmp = ev;
	ex_ev = malloc(sizeof(char *) * ((ft_lstlast(tmp))->index + 2));
	if (!ex_ev)
		return (NULL);
	i = 0;
	while (tmp)
	{
		ex_ev[i] = ft_strjoin_t(tmp->key, "=", tmp->value);
		i++;
		tmp = tmp->next;
	}
	ex_ev[i] = NULL;
	return (ex_ev);
}
