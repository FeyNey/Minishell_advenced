/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:07:58 by alexis            #+#    #+#             */
/*   Updated: 2024/10/11 22:57:11 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **value)
{
	int i;
	int sw;

	i = 1;
	sw = 0;
	if (value[1][0] == '-')
		sw = ft_echo_option(value[1]);
	if (sw == 1 && !(value[2]))
		return(1);
	if (sw == 1)
		i = 2;
	{
		while(value[i])
		{
			ft_printf("%s", value[i]);
			i++;
			if (value[i])
				ft_printf(" ");
		}
	}
	if (sw == 0)
		ft_printf("\n");
	return(0);
}

int	ft_echo_option(char *value)
{
	int i;

	i = 1;
	if (value[1] == 'n')
	{
		while(value[i] == 'n')
		{
			i++;
		}
		if (!(value[i]))
			return(1);
	}
	return (0);
}
