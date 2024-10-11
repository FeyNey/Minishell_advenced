/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:20:48 by acoste            #+#    #+#             */
/*   Updated: 2024/10/11 13:27:02 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	isredir_ok(t_token *t)
{
	int	i;

	if (!t)
		return (0);
	i = 0;
	while (t->value[i])
	{
		if (redir_type(t->value[i]))
		{
			if (!owr(t->value[i]) && !(t->value[i + 1]))
			{
				print_err(t->value[i]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	is_ok(t_bag **bag)
{
	t_token	*t;

	if (!pipok(bag))
	{
		return (0);
	}
	t = (*bag)->tokens;
	while (t)
	{
		if (!(isredir_ok(t)))
			return (0);
		t = t->next;
	}
	return (1);
}

int	pipok(t_bag **bag)
{
	int		flag;
	int		i;
	t_token	*t;

	i = 0;
	t = (*bag)->tokens;
	if (!t)
		return (0);
	while (t)
	{
		if ((i % 2) && t->type == PIPE)
			flag = 0;
		else
			flag = 1;
		t = t->next;
		i++;
	}
	if (!flag)
	{
		print_err("|");
		return (0);
	}
	return (1);
}

void	cleanpip(t_token **t)
{
	t_token	*to;
	t_token	*tmp;

	to = (*t);
	while (to)
	{
		tmp = to->next;
		if (tmp && tmp->type == PIPE)
		{
			to->next = tmp->next;
			free(tmp);
		}
		to = to->next;
	}
}
