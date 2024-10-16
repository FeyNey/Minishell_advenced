/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:51:49 by alexis            #+#    #+#             */
/*   Updated: 2024/10/12 22:55:46 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_args(char **command)
{
	int	i;

	i = 0;
	if (command[1][i] == '-' || command[1][i] == '+')
		i++;
	while (command[1][i])
	{
		if ((command[1][i] < '0' || command[1][i] > '9'))
		{
			ft_printf("bash: exit: %s: numeric argument required", command[1]);
			return (global_variable(1, 0), 1);
		}
		i++;
	}
	i = 0;
	while (command[i])
		i++;
	if (i > 2)
	{
		ft_printf("bash: exit: too many arguments\n");
		return (global_variable(1, 0), 2);
	}
	return (1);
}

int	ft_exit(char **command, t_env **env, t_token **tok, t_bag *bag)
{
	{
		write(1, "exit\n", 5);
		if (!command[1])
		{
			ft_free_all(env, tok, bag);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (check_exit_args(command) == 1)
			{
				ft_free_all(env, tok, bag);
				exit(EXIT_SUCCESS);
			}
		}
	}
	return (0);
}

void	ft_free_all(t_env **env, t_token **tok, t_bag *bag)
{
	free_env(*env);
	free_tokens(*tok);
	free(bag);
}
