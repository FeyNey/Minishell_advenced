/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:48:54 by aglampor          #+#    #+#             */
/*   Updated: 2024/10/11 19:26:05 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token *p)
{
	t_token	*tmp;

	if (!p)
		return ;
	while (p)
	{
		tmp = p->next;
		if (p->value)
			ft_free_split(p->value);
		free(p);
		p = tmp;
	}
}

int	end_tok(char *s)
{
	int		i;
	int		flag;
	char	prev;

	i = 0;
	if (s[i] == '|')
		return (1);
	prev = '\0';
	flag = 0;
	while (s[i])
	{
		if (!flag && (prev != '\\' && is_quote(s[i])))
			flag = is_quote(s[i]);
		else if (!flag && (s[i] == '|' && prev != '\\'))
			return (i);
		else if (flag && prev != '\\' && s[i] == flag)
			flag = 0;
		prev = s[i];
		i++;
	}
	return (i);
}

int	end_cmd(char *s)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (s[i])
	{
		if (!flag && (is_quote(s[i])))
			flag = is_quote(s[i]);
		else if (!flag && is_white(s[i]))
			return (i);
		else if (s[i] == flag)
			return (i + 1);
		i++;
	}
	return (i);
}

void	ft_addb_tok(t_token **p, t_token *new)
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

int	type_tok(char *s, t_env *env)
{
	if (s[0] == 45)
		return (OPTION);
	else if (s[0] == '/')
		return (DIRECTORY);
	else if (is_builtin(s))
		return (BUILTIN);
	else if (is_cmd(s, env))
		return (CMD);
	else if (!ft_cmp(s, "|"))
		return (PIPE);
	return (0);
}
