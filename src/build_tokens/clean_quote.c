/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:22:37 by aglampor          #+#    #+#             */
/*   Updated: 2024/10/11 13:19:05 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	have_quote(char *cmd)
{
	int		i;
	int		flag;
	char	prev;

	i = 0;
	flag = 0;
	prev = '\0';
	while (cmd[i])
	{
		if (!flag && (prev != '\\' && is_quote(cmd[i])))
			flag = is_quote(cmd[i]);
		else if (flag && (prev != '\\' && is_quote(cmd[i]) == flag))
			return (1);
		prev = cmd[i];
		i++;
	}
	return (0);
}

int	mal_no_quote(char *cmd)
{
	int		i;
	int		flag;
	int		n_mall;
	char	prev;

	flag = 0;
	n_mall = 0;
	i = 0;
	prev = '\0';
	while (cmd[i])
	{
		if (!flag && (prev != '\\' && is_quote(cmd[i])))
			flag = is_quote(cmd[i]);
		else if (flag && (prev != '\\' && is_quote(cmd[i]) == flag))
			flag = 0;
		else if (prev != '\\')
			n_mall++;
		prev = cmd[i];
		i++;
	}
	return (n_mall + 1);
}

void	dup_no_quote(char *cmd, char *new)
{
	int		i;
	int		flag;
	char	prev;

	i = 0;
	flag = 0;
	prev = '\0';
	while (*cmd)
	{
		if (!flag && (prev != '\\' && is_quote(*cmd)))
			flag = is_quote(cmd[i]);
		else if (flag && (prev != '\\' && is_quote(*cmd) == flag))
			flag = 0;
		else if (prev != '\\')
		{
			new[i] = *cmd;
			i++;
		}
		prev = *cmd;
		cmd++;
	}
	new[i] = '\0';
}

void	remove_quote(t_token **t)
{
	int			i;
	t_token		*tmp;
	char		*new;

	tmp = (*t);
	i = 0;
	while (tmp->value[i])
	{
		if (!(have_quote(tmp->value[i])))
			i++;
		else
		{
			new = malloc(sizeof(char) * mal_no_quote(tmp->value[i]));
			if (!new)
				return ;
			dup_no_quote(tmp->value[i], new);
			free((*t)->value[i]);
			(*t)->value[i] = new;
			i++;
		}
	}
}
