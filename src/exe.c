/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:21:36 by aglampor          #+#    #+#             */
/*   Updated: 2024/10/03 17:36:21 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_cmd(t_token	*ts, t_env **e)
{
	if (!ft_cmp("export", ts->value[0]))
		return (ft_export(ts, e));
	else if (!ft_cmp("env", ts->value[0]))
		return (ft_env(ts, *e));
	else if (!ft_cmp("unset", ts->value[0]))
		return (ft_unset(ts->value, e));
	// else if (!ft_cmp("cd", ts->value[0]))
	// 	return (ft_cd(ts->value, e));
	else if(!ft_cmp("exit", ts->value[0]))
		return (ft_exit(ts->value, e, &ts));
	return (0);
}
