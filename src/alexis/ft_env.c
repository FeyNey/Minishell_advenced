/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:25:02 by acoste            #+#    #+#             */
/*   Updated: 2024/08/27 15:25:28 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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