/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/24 17:27:04 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	minishell(t_env *env)
{
	char	*line;
	t_token	*toks;
	int		run;

	run = 1;
	while (run)
	{
		line = readline("MY_minishell : ");
		if (!line)
		{
			write(1, "exit\n", 5);
			clear_history();
			return (0);
		}
		if (is_empty_line(line) == 0)
			add_history(line);
		toks = NULL;
		build_tokens(line, &toks, env);
	}
	clear_history();
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	t_env		*env;

	(void)ac;
	(void)av;
	env = NULL;
	init_env(&env, ev);
	rl_catch_signals = 0;
	redirect_signals();
	minishell(env);
	free_env(env);
	return (0);
}
