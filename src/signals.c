/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:21:27 by acoste            #+#    #+#             */
/*   Updated: 2024/10/12 19:05:10 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	print_err(char *t)
{
	printf("bash: syntax error near '%s' unexpected token\n", t);
}

void	sigquit_handler(int signal)
{
	(void)signal;
}

void	redirect_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGTSTP, sigquit_handler);
}
