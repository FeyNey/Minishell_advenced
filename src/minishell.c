/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/21 17:45:51 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	minishell(t_bag **bag)
{
	char	*line;

	while (1)
	{
		line = readline("MY_minishell : ");
		if (!line || !ft_cmp("exit", line))
		{
			write(1, "exit\n", 5);
			clear_history();
			return (free(line), 0);
		}
		if (!is_empty_line(line))
			add_history(line);
		(*bag)->tokens = NULL;
		build_tokens(line, bag);
		free(line);
		if ((*bag)->tokens)
			s_exe((*bag)->tokens, &(*bag)->env);
		free_tokens((*bag)->tokens);
	}
	clear_history();
	return (0);
}

int	s_exe(t_token *t, t_env **menv)
{
	if (t->type == BUILTIN || t->type == CMD)
		return (ex_cmd(t, menv));
	else
		write(1, "Reflexion++\n", 12);
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	t_bag	*bag;

	(void)av;
	(void)ac;
	if (!(bag = malloc(sizeof(t_bag)))) //pas possible
		return (1);
	bag->env = NULL;
	init_env(&(bag->env), ev);
	// rl_catch_signals = 0;
	// redirect_signals();
	minishell(&bag);
	free_env((bag->env));
	free(bag);
	return (0);
}