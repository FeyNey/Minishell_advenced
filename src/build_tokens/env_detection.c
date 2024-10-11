/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_detection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:55:55 by alexis            #+#    #+#             */
/*   Updated: 2024/10/11 14:01:43 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_between_quote_and_has_venv(char *word)
{
	int		i;
	int		f;
	char	prev;

	i = 0;
	f = 0;
	prev = word[i];
	while (word[i])
	{
		if (word[i] == 39 && not_between_quote(word, word[i], i) == 1)
		{
			i++;
			while (word[i] != 39 && word[i] != '\0')
				i++;
		}
		if ((word[i] == '$') && (prev != 92)
			&& (is_env_char2(word[i + 1]) == 0))
			f = 1;
		prev = word[i];
		i++;
	}
	if (f == 1)
		return (1);
	else
		return (0);
}

int	is_valable_venv(char *word)
{
	int		i;
	char	prev;

	i = 0;
	prev = word[i];
	while (word[i])
	{
		if (word[i] == 39 && not_between_quote(word, word[i], i) == 1)
		{
			i++;
			while (word[i] != 39 && word[i] != '\0')
				i++;
		}
		if ((word[i] == '$') && (prev != 92))
		{
			if (word[i + 1])
				return (i);
		}
		prev = word[i];
		i++;
	}
	return (-1);
}

int	not_between_quote(char *str, char c, int j)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
				i++;
		}
		if (str[i] == c && i == j)
			return (1);
		i++;
	}
	return (0);
}

char	*found_in_env(t_env **env, int index)
{
	t_env	*tmp;
	char	*value;
	int		i;

	i = 0;
	tmp = (*env);
	while (i < index)
	{
		(*env) = (*env)->next;
		i++;
	}
	value = (*env)->value;
	(*env) = tmp;
	return (value);
}

int	is_in_ev_tok(char *arg, t_env *myev, int flag)
{
	char	*k;
	int		targ;
	t_env	*tmp;

	tmp = myev;
	targ = 0;
	while (is_env_char(arg[flag]) == 0)
		flag++;
	k = word_dup(arg, 0, flag);
	while (myev)
	{
		if (!ft_cmp(myev->key, k))
		{
			if (flag >= 0)
				free(k);
			myev = tmp;
			return (targ);
		}
		targ++;
		myev = myev->next;
	}
	if (k)
		free(k);
	myev = tmp;
	return (-1);
}
