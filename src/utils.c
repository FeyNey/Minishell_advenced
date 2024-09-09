/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:59:27 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/09 23:35:47 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	is_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}


int	c_find(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] != c)
		i++;
	return (i);
}

int	ft_cmp(char *o, char *t)
{
	int	i;

	i = 0;
	while (o[i])
	{
		if (o[i] != t[i])
			return (o[i] - t[i]);
		i++;
	}
	return (o[i] - t[i]);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(dup))
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_quote(char c)
{
	if (c == 34)
		return (34);
	else if (c == 39)
		return (39);
	return (0);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (line[i] == '\0')
		return (1);
	else
		return (0);
}