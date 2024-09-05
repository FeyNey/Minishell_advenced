/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:38:59 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/03 20:55:42 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **tab)
{
	int i;
	int f;

	i = 1;
	f = 0;
	if (!tab[1] || is_empty_line(tab[1]) == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (tab[i][0] == '-' && tab[i][1] == 'n')
	{
		i++;
		f = 1;
	}
	while (tab[i])
	{
		ft_putstr(tab[i]);
		if (tab[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (f == 0)
		write(1, "\n", 1);
	return (0);
}

void	ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!dest || !src)
		return ;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

void	build_prompt(char *prompt)
{
	char	cwd[1024];

	ft_strcpy("minishell : ", prompt);
	if (!(getcwd(cwd, sizeof(cwd))))
		perror("getcwd");
	ft_strcat(prompt, cwd);
	ft_strcat(prompt, "$ ");
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

static int	minishell(t_bag **bag)
{
	char	prompt[1024];
	char	*line;

	while (1)
	{
		build_prompt(prompt);
		line = readline(prompt);
		if (!line || !ft_cmp("exit", line))
		{
			write(1, "exit\n", 5);
			clear_history();
			break ;
		}
		if (is_empty_line(line) == 0)
			add_history(line);
		(*bag)->tokens = NULL;	//fonction reset_token(bag->tokens) qui free (et pointe vers null)
		build_tokens(line, bag);
//		s_exe(toks, env);
		free_tokens((*bag)->tokens);
	}
	free(line);
	clear_history(); // !q clear if add_history has been past maybe to check
	return (0);
}

int	s_exe(t_token *ts, t_env **e)
{
//	if (ft_verif_line())
//		return (1);
	if (!ts)
		return (0);
	if (ts->type == BUILTIN || ts->type == CMD)
		return (ex_cmd(ts, e));
	else
		write(1, "Reflexion++\n", 12);
	return (0);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

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

int	main(int ac, char **av, char **ev)
{
	t_bag	*bag;

	(void)av;
	if (!(bag = malloc(sizeof(t_bag))))
		return (100); // !q
	bag->env = NULL;
	init_env(&(bag->env), ev);
	//display_env(&(bag->env));
	rl_catch_signals = 0;
	redirect_signals();
	minishell(&bag);
	free(bag);
	return (ac);
}
/*

supprimer les redirections,
supprimer les quotes;

appliquer les pipes | redir

les quelques builtin;
*/