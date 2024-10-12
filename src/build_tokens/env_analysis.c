/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:59:54 by alexis            #+#    #+#             */
/*   Updated: 2024/10/12 20:17:28 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*number_venv(char *str, int i)
{
	char	*new;
	int		y;

	if (str[i + 1] == '0')
		return (replace_venv4(str, i, i + 2, "minishell"));
	else
	{
		y = 0;
		new = ft_malloc(ft_strlen(str) - 2);
		i = 0;
		while (i < is_valable_venv(str))
			new[y++] = str[i++];
		i = i + 2;
		while (str[i])
			new[y++] = str[i++];
	}
	return (new);
}

int	is_env_char(char c)
{
	if (c == '$')
		return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (0);
	else
		return (1);
}

// list des caracteres pouvant suivre un $ et aillant une modification
// particuliere, exemple les $+ doivent rester les meme, si un $ n as
// pas de lettre apres il doit rester ect...
// liste des caracteres a modifie
// ne prend pas en compte $#, $_, $!, $*

int	is_env_char2(char c)
{
	if (c == 0)
		return (1);
	else if (c == ' ')
		return (1);
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')
		|| (c >= '0' && c <= '9') || (c == '-') || (c == '$') || (c == 34)
		|| (c == 39) || (c == '?'))
		return (0);
	else
		return (1);
}

char	*skip_venv(char *str, int i, int j)
{
	char	*new;
	char	*stock;

	if (str[i + 1] >= '0' && str[i + 1] <= '9')
		return (number_venv(str, i));
	else if (str[i + 1] == '$')
	{
		stock = ft_itoa((int)getpid());
		new = replace_venv4(str, i, i + 2, stock);
		return (free(stock), new);
	}
	else if (str[i + 1] == '-')
		return (replace_venv4(str, i, (j + 1), "himBHs"));
	else if (str[i + 1] == 34 || str[i + 1] == 39)
		return (replace_venv4(str, i, j, ""));
	else if (str[i + 1] == '?')
	{
		stock = ft_itoa(global_variable(0, 1));
		new = replace_venv4(str, i, i + 2, stock);
		return (free(stock), new);
	}
	else
		return (skip_venv2(str, i, j));
}

char	*skip_venv2(char *str, int i, int j)
{
	char	*new;
	int		x;
	int		y;

	x = 0;
	y = 0;
	new = ft_malloc(ft_strlen(str) - (j - i));
	while (x < is_valable_venv(str))
		new[y++] = str[x++];
	if (is_env_char(str[x + 1]) == 0)
		x++;
	while (is_env_char(str[x]) == 0)
		x++;
	while (str[x])
		new[y++] = str[x++];
	new[y] = '\0';
	return (new);
}
