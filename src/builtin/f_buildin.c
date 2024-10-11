/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_buildin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:59:06 by aglampor          #+#    #+#             */
/*   Updated: 2024/10/11 09:07:30 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_token *t, t_env **myEnv)
{
	int	err;

	if (t->value[1])
		err = export_args(t, myEnv, 1);
	else
		err = export_no_arg(*(myEnv));
	return (err);
}

int	ft_env(t_token *t, t_env *menv)
{
	t_env	*tmp;

	if (t->value[1])
		return (1);
	tmp = menv;
	while (tmp)
	{
		if (tmp->value[0] != '\0')
		{
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset(char **cmds, t_env **menv)
{
	int	i;
	int	id_targ;

	i = 0;
	while (cmds[i])
	{
		id_targ = is_in_ev(cmds[i], (*menv));
		if (ft_cmp("_", cmds[i]) != 0 && id_targ != -1)
			ft_delnode_idx(menv, id_targ);
		else
			i++;
	}
	return (0);
}
