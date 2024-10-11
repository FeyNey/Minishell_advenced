/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:00:59 by alexis            #+#    #+#             */
/*   Updated: 2024/10/11 14:03:36 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_venv1(t_token *tok, t_env **env, char **str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[j])
	{
		i = is_between_quote_and_has_venv(str[j]);
		if (i == 1)
		{
			new = replace_venv2(tok->value[j], env);
			tok->value[j] = new;
		}
		else
			j++;
	}
}

char	*replace_venv2(char *str, t_env **env)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		i = is_valable_venv(str);
		if (i == -1)
			break ;
		if (str[i] == '$')
		{
			j = i + 1;
			while ((is_env_char(str[j]) == 0) && (str[j]))
				j++;
			new = replace_venv3(str, env, i, j);
			str = new;
			i = 0;
		}
	}
	return (str);
}

char	*replace_venv3(char *str, t_env **env, int i, int j)
{
	char	*new;
	int		f;

	f = is_in_ev_tok(str + i + 1, *env, 0);
	if (f >= 0)
	{
		new = replace_venv4(str, i, j, found_in_env(env, f));
	}
	else if (f == -1)
	{
		new = skip_venv(str, i, j);
	}
	free(str);
	return (new);
}

char	*replace_venv4(char *str, int i, int j, char *value)
{
	int		x;
	int		y;
	int		diff;
	char	*new;

	x = 0;
	diff = (j - i);
	new = ft_malloc((ft_strlen(str) + ft_strlen(value) - (j - i)));
	new[(ft_strlen(str) - j) + (ft_strlen(value))] = '\0';
	i = 0;
	y = 0;
	while (i < is_valable_venv(str))
		new[y++] = str[i++];
	while (value[x])
		new[y++] = value[x++];
	i = i + diff;
	while (str[i])
		new[y++] = str[i++];
	new[y] = '\0';
	return (new);
}
