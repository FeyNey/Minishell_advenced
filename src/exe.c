/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:21:36 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/18 12:37:03 by alexis           ###   ########.fr       */
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
	return (0);
}
