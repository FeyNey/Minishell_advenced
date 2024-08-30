/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:51:13 by acoste            #+#    #+#             */
/*   Updated: 2024/08/30 19:36:18 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

char	*ft_malloc(int len)
{
	char	*new;
	int i;

	i = 0;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = '\0';
	while (i < len)
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}

char *ft_clear_quote(t_token **tok, t_env **env)
{
	int i;

	i = 0;
	while ((*tok)->next)  // WHILE LEN struct TOKEN;
	{
//		while ((*tok)->value[i][0])
//		{
			if ((*tok)->value[i][0] == 34)
			{
				(*tok)->value[i] = ft_new_token34((*tok)->value[i], env);
				i++;
			}
			else if ((*tok)->value[i][0] == 39)
			{
				(*tok)->value[i] = ft_new_token39(tok, env);
				i++;
			}
//		}
		*tok = (*tok)->next;
	}
}		//NEED 1 MORE EXECUTION

int	*ft_strlen_token(char *str, t_env **env)
{
	int i;

	i = 0;
	while ((*env)->next)
	{

		if (ft_strncmp(str, (*env)->key, ft_strlen(str)) == 0)
		{
			i += ft_strlen((*env)->value);
		}
		else
		{
			env = (*env)->next;
		}
	}
	return (i);
}

char	*new_token34(char *str, t_env **env)
{
	char *new_tok;
	int i;
	int len;

	len = ft_strlen_token(str, env);
	new_tok = ft_malloc(len);
	i = 1;
	while(str[i] != 34)
	{
		if (str[i] == '$')
		{
			find_env(str + i + 1, env, new_tok);
		}
		else
		{
			new_tok[i] = str[i];
		}
		i++;
	}
	free(str);
}


void	find_env(char *str, t_env **env, char new_token)
{
	int i;

	i = 0;
	while ((*env)->next)
	{
		if (ft_strncmp(str, (*env)->key, ft_strlen(str)) == 0)
		{
		}
	}
}
