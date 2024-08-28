/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 22:13:05 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/27 15:39:23 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	m_exit(int code, char *val)
{
	if (code == 1)
		return ;
	if (code == 2)
	{
		ft_putstr_fd("bash : synthax error near\n", 2);
		ft_putstr_fd("unexpected token", 2);
	}
	if (code == 126 || code == 127)
		write(2, "bash: ", 6);
	write(2, val, ft_lenstr(val));
	if (code == 126)
		write(2, ": Is a directory", 16);
	if (code == 127)
		write(2, ": command not found", 19);
}
*/