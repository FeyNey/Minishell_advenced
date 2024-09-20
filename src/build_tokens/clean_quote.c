/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:06:39 by alexis            #+#    #+#             */
/*   Updated: 2024/09/20 06:03:57 by alexis           ###   ########.fr       */
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
		if (!flag && (prev != '\\' && (flag = is_quote(cmd[i]))))
			; // WTF??
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
		if (!flag && (prev != '\\' && (flag = is_quote(cmd[i]))))
			; //WTF
		else if (flag && (prev != '\\' && is_quote(cmd[i] == flag)))
			flag = 0;
		else if (prev != '\\')
			n_mall++;
		prev = cmd[i];
		i++;
	}
	return (n_mall + 1);
}
			
char	*dup_no_quote(char *cmd)
{
	int		i;
	int		flag;
	char	prev;
	char	*new;

	new = malloc(sizeof(char) * mal_no_quote(cmd));
	if (!new)
		return (NULL);
	i = 0;
	flag = 0;
	prev = '\0';
	while (*cmd)
	{
		if (!flag && (prev != '\\' && (flag = is_quote(*cmd))))
			; //WTF
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
	return (new);
}

void	remove_quote(t_token **t)
{
	int		i;
	char	*new;
	t_token	*tmp;

	tmp = (*t);
	i = 0;
	while (tmp->value[i])
	{
		printf("%s\n", tmp->value[i]);
		if (!(have_quote(tmp->value[i])))
			i++;
		else
		{
			new = dup_no_quote(tmp->value[i]);
			printf("cleaned  %s\n", new);
			free((*t)->value[i]);
			(*t)->value[i] = new;
			i++;
		}
	}
}
