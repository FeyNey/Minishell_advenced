/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:08:58 by acoste            #+#    #+#             */
/*   Updated: 2024/08/27 17:13:48 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putnstr(char *str, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(1, &str[i], 1);
		i++;
	}
}


int	ft_echo(t_token **token, t_env **env)
{
	int i;
	int s;

	i = 1;
	s = 0;
	if (!(*token)->value[1] || is_empty_line((*token)->value[1]) == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	if ((*token)->value[i][0] == '-')
	{
		*token = (*token)->next;
		i++;
		s = 1;
	}
	return (ft_echo2(token, env, s, i));
}

int	ft_echo2(t_token **token, t_env **env, int s, int i)
{
	int len;
	int j;

	j = 0;
	while ((*token)->value[i])
	{
		if ((*token)->value[i][0] == '$')
			return (ft_echo3(token, env, s, i));
		len = ft_strlen((*token)->value[i]);
		ft_putnstr((*token)->value[i], len);
		i++;
		if ((*token)->value[i])
			write (1, " ", 1);
		if (s == 0)
			write(1, "\n", 1);
	}
	return (0);
}

int	ft_echo3(t_token **token, t_env **env, int s, int i)
{

}