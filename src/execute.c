/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:21:36 by aglampor          #+#    #+#             */
/*   Updated: 2024/10/12 23:13:04 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_exe(t_token *t, t_env **menv)
{
	int	out;

	if (t->fdin)
		dup2(t->fdin, 0);
	if (t->fdout)
		dup2(t->fdout, 1);
	if (t->type == BUILTIN)
		out = exe_builtin(t, menv);
	else
		out = exe_shell(t, *menv);
	if (t->fdin)
		close(t->fdin);
	if (t->fdout)
		close(t->fdout);
	return (out);
}

void	pipe_end(t_bag *bag)
{
	free_tokens(bag->tokens);
	free_env(bag->env);
	free(bag);
	exit(global_variable(0, 1));
}

int	tokens_exe(t_token *t, t_env **env, t_bag *bag)
{
	int		**pipefd;
	int		nb_tok;

	nb_tok = nb_token(t);
	if (!t->next && t->type == BUILTIN)
		return (cmd_exe(t, env));
	exit_exe(bag, t->value);
	pipefd = build_pipe(nb_tok);
	child_exec(bag, pipefd, 0, nb_tok);
	return (0);
}

int	child_exec(t_bag *bag, int **pipefd, int i, int nb_tok)
{
	int		status;
	pid_t	pid;

	pipefd = build_pipe(nb_tok);
	while (bag->tokens)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		else if (!pid)
		{
			handle_pip(pipefd, i);
			free_pipes(pipefd);
			cmd_exe(bag->tokens, &(bag->env));
			pipe_end(bag);
		}
		else
		{
			// waitpid(pid, &status, 0);
			global_variable(WEXITSTATUS(status), 0);
		}
		bag->tokens = bag->tokens->next;
		i++;
	}
	return (daddy_rout(pipefd, nb_tok, pid), 0);
}

/*
int	tokens_exe(t_token *t, t_env **env, t_bag *bag, int	i)
{
	pid_t	pid;
	int		**pipefd;
	int		nb_tok;

	nb_tok = nb_token(t);
	if(!t->next && t->type == BUILTIN)
			return (exe_builtin(t, env));
	pipefd = build_pipe(nb_tok);
	while (t)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (!pid)
		{
			handle_pip(pipefd, i);
			free_pipes(pipefd);;
			cmd_exe(t, env);
			ft_free_all(env, &t, bag);
			exit(1);
		}
		t = t->next;
		i++;
	}
	return (daddy_rout(pipefd, nb_tok, pid), 0);
}
*/

void	error_execve(char **value)
{
	printf("Error code: \n%d\n", errno);
	if (errno == 2)
		global_variable(127, 0);
	printf("bash : %s: %s\n", value[0], strerror(errno));
}


int	exe_shell(t_token *t, t_env *menv)
{
	char	**exe_env;
	char	*t_path;

	exe_env = get_ex_env(menv);
	if (!find_c(t->value[0], '/'))
	{
		if (!(access(t->value[0], F_OK | X_OK)))
			t_path = t->value[0];
		else
		{
			ft_free_split(exe_env);
			return (1);
		}
	}
	else
	{
		t_path = tru_path(t->value[0], menv);
	}
	if (t_path)
	{
		if (execve(t_path, t->value, exe_env) == -1)
			error_execve(t->value);
	}
	ft_free_split(exe_env);
	return (0);
}

int	exe_builtin(t_token *ts, t_env **e)
{
	if (!ft_cmp("export", ts->value[0]))
		return (ft_export(ts, e));
	else if (!ft_cmp("env", ts->value[0]))
		return (ft_env(ts, *e));
	else if (!ft_cmp("unset", ts->value[0]))
		return (ft_unset(ts->value, e));
	else if (!ft_cmp("pwd", ts->value[0]))
		return (ft_pwd(ts->value));
	else if (!ft_cmp("cd", ts->value[0]))
		return (ft_cd(ts->value, e));
	else if (!ft_cmp("echo", ts->value[0]))
		return (ft_echo(ts->value));
	return(0);
}
