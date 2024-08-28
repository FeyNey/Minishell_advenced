/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/27 20:36:35 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static int	is_pipe(t_token *t)
{
	t_token	*temp;

	temp = t;
	while (temp)
	{
		if(temp->type == PIPE)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static int	minishell(t_env **env)
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
		build_tokens(line, &toks, *env);
		if (!is_pipe(toks))
			s_exe(toks, env);
		else
			write(1, "JE GG PA I A D PIPE\n", 20);
	}
	clear_history();
	return (0);
}

int	s_exe(t_token *ts, t_env **e)
{
	if (!ts)
		return (0);
	if (ts->value == 0)
		return (0);
	if (ts->type == BUILTIN || ts->type == CMD)
		return (ex_cmd(ts, e));
	else
		write(1, "Reflexion++\n", 12);
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	t_env		*env;

	(void)ac;
	(void)av;
	env = NULL;
	init_env(&env, ev);
	env->pid = getpid();
	rl_catch_signals = 0;
	redirect_signals();
	minishell(&env);
	free_env(env);
	return (0);
}
