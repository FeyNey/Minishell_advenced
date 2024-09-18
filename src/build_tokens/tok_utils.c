/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:48:54 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/16 01:03:45 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void    free_tokens(t_token  *p)
{
        t_token   *tmp;

        while (p)
        {
                tmp = p->next;
		if (p->value)
			ft_free_split(p->value);
                free(p);
                p = tmp;
        }
}

int	type_redir(char *str)
{
	printf("ft_cmp et diff resultat\n");
	return (str[0]);
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
		if (!flag && prev != '\\')
			flag = is_quote(s[i]);
		if (!flag && (s[i] == '|' && prev != '\\'))
			return (i);
		if (flag && s[i] != '\\' && s[i + 1] == flag)
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
	int	q;
	
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (!flag && (q = is_quote(s[i])))
			flag = q;
		else if (!flag && is_white(s[i]))
			return (i);
		else if (s[i] == flag)
			flag = 0;;
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
	printf("type_tok\n");
	if (s[0] == 45)
		return (OPTION);
	else if (s[0] == '/')
		return (DIRECTORY);
	else if (is_builtin(s))
		return (BUILTIN);
	else if (is_cmd(s, env))
		return (CMD);
	return (0);
}

