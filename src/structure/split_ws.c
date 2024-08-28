/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ws.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:51:30 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/26 19:07:29 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_white(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	white_words(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*str)
	{
		if (!(is_white(*str)) && flag == 0)
		{
			flag = 1;
			i++;
		}
		else
			flag = 0;
		str++;
	}
	return (i);
}

char	**splt_white(char *s)
{
	int		i;
	int		j;
	int		index;
	char	**split;

	split = malloc((white_words(s) + 1) * sizeof(char *));
	if (!s || !(split))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (!(is_white(s[i])) && index < 0)
			index = i;
		else if ((is_white(s[i]) || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
