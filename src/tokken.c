/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:16:34 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/23 19:44:01 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_addb_tok(t_token **p, t_token *new)
{
	t_token	*temp;

	if (!*p)
		*p = new;
	else
	{
		temp = *p;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static int	end_tok(char *s)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (s[i] == 39 || s[i] == 34)
	{
		flag = (int)s[i];
		i++;
	}
	while (s[i])
	{
		if (flag == 0 && (is_white(s[i]) || s[i] == 39 || s[i] == 34))
			return (i);
		if (flag && s[i] == flag)
			return (i + 1);
		i++;
	}
	return (i);
}

static int	type_tok(char *s, t_env *env)
{
	int	val;

	printf("%d\n", s[0]);
	if ((val = open(s, O_RDONLY, 0776)) != -1)
	{
		close(val);
		return (FD);
	}
	else if (s[0] == 45)
		return (OPTION);
	else if (s[0] == '/')
		return (DIRECTORY);
	else if ((val = is_redir(s)) != 0)
		return (val);
	else if (is_builtin(s))
		return (BUILTIN);
	else if (is_cmd(s, env))
		return (CMD);
	return (0);
}

static int	bt_u(char *l, t_token **t, t_env *env)
{
	int		j;
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	j = end_tok(l);
	new->value = word_dup(l, 0, j);
	new->type = type_tok(new->value, env);
	new->next = 0;
	ft_addb_tok(t, new);
	return (j);
}

void	printtok(t_token **t)
{
	t_token	*temp;

	temp = *t;
	while (temp)
	{
		printf("value %s\n", temp->value);
		printf("type %d\n", temp->type);
		temp = temp->next;
	}
}

void	build_tokens(char *line, t_token **t, t_env *env)
{
	int	i;

	i = 0;
	while (line[i] && i < ft_strlen(line))
	{
		while (is_white(line[i]))
			i++;
		if (line[i])
			i += bt_u(&line[i], t, env);
	}
	printtok(t);
}
