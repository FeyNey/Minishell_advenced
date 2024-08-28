/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:21:36 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/27 15:43:46 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ex_cmd(t_token	*ts, t_env **e)
{
	if (ts->type == CMD)
		printf("HAVE to code CMD\n");
	else if (!ft_cmp("export", ts->value))
		return (export(ts, e));
	else if (!ft_cmp("echo", ts->value))
		return (echo(ts, e));
//	return (printf("CODE the next BUILTIN\n"));
	return (0);
}
