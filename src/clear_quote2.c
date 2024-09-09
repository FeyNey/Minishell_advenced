/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:00:59 by alexis            #+#    #+#             */
/*   Updated: 2024/09/09 23:49:22 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//utils

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

//utils

int tok_len(t_token **tok)
{
	int i;

	i = 0;
	while ((*tok)->next)
		i++;
	i++;
	return (i);
}

//replace $ | than | supp quote

void	clear_token(t_token **tok, t_env **env) // valeur de retour pour l erreur ?
{
	int i;
	int j;
	
	i = 0;
	j = tok_len(tok);
	while (i < j)
	{
		replace_$(*tok, env, (*tok)->value); //verif
		supp_quote(tok, (*tok)->value); //verif
		(*tok) = (*tok)->next;
		i++;
	}
}

void	supp_quote(t_token **tok, char **str)
{
	char *new;
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == 34 || str[i][0] == 39)
		{
			new = supp_quote2(tok, str[i]);
			(*tok)->value[i] = new;
		}
		i++;
	}
}

char *supp_quote2(t_token **tok, char *str)
{
	char *new;
	int max;
	int i;
	int j;
	
	(void)tok;
	max = ft_strlen(str);
	max = max - 2;
	new = ft_malloc(ft_strlen(str) - 2);
	new[ft_strlen(str) - 2] = '\0';
	i = 1;
	j = 0;
	while (j < max)
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

// replace_$
// si entre quote

void	replace_$(t_token *tok, t_env **env, char **str)
{
	int i;
	int j;
	char *new;
	
	i = 0;
	j = 0;
	while (str[j])
	{
		i =	is_between_quote_and_has_$(str[j]);
		if (i == 1)
		{
			new = replace_$2(str[j], env);
			free(str[j]);
			tok->value[j] = new;
		}
		j++;
	}
}

int	is_between_quote_and_has_$(char *word)
{
	int i;
	int f;

	i = 0;
	f = 0;
	while (word[i])
	{
		if (word[i] == '$')
			f = 1;
		i++;
	}
	if (word[0] == 34 && f == 1) // ?
		return (1); // remplace
	else if (word[0] == 39)
		return (2); // remplace pas
	else
		return (0); // remplace pas
}

char *replace_$2(char *str, t_env **env)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	
	while (i < ft_strlen(str))
	{
		while (str[i] != '$')
			i++;
		if (str[i] == '$')
		{
			while (is_env_char(str[j] == 0))
				j++;
			new = replace_$3(str, env, i, j);
		}
		if (str[i] != '\0')
			i++;
	}
	return (new);
}
/*
	while (j < i)
	{
		while(str[i] != '$' || str[i])
			i++;
		if (str[i] == '$')
		{
			i++;
			if (str[i] >= '0' || str[i] <= '9')
			{
				if (str[i] == '0')
					replace_token(); // TODO -> minishell(/0) //duppliquer toute la chaine et remplacer $0 ou $ par rien ou minishell
				return (ft_malloc(0));
			}
			else
				new = replace_$3(str, env);
		}
	}
*/

char *replace_$3(char *str, t_env **env, int i, int j)
{
	char *new;
	int f;

	f = 0;
	while ((*env)->next)
	{
		if (ft_strncmp(str + i, (*env)->key, j) == 0)
		{
			new = replace_venv(str, i, j, (*env)->value); // changer la variable env apres le $ numero j si new existe, le free et en remalloc un
			f = 1;
		}
		(*env) = (*env)->next;
	}
	if (ft_strncmp(str + i, (*env)->key, j) == 0)
	{
		new = replace_venv(str, i, j, (*env)->value); // changer la variable env apres le $ numero j si new existe, le free et en remalloc un
		f = 1;
	}
	if (f == 0)
			new = replace_venv(str, 0, 0, new);
	i++; // ??
	return (new);
}

char *replace_venv(char *str, int i, int j, char *value)
{
	int x;
	char *new;
	
	x = 0;
//	while (str[i] != '$' || str[i])
//		i++;
//	if (str[i] == '\0')
//		write (1, "Unprevius beavior, no $ in the sentence\n", 40);
	new = ft_malloc((ft_strlen(str) - j) + (ft_strlen(value)));
	new[(ft_strlen(str) - j) + (ft_strlen(value))] = '\0';
	i = 0;
	j = 0;
	while (str[i] != '$')
	{
		new[j] = str[i];
		i++;
		j++;
	}
	i++;
	while (value[x])
	{
		new[j] = value[x];
		j++;
		x++;
	}
	while (str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (new);
}

/*reprendre ici, 

il reste a comparer tout l'environnement, 	remplacer si je tomber sur un element valide,
											remplacer si je ne tombe sur rien;	

*/

int	is_env_char(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') 
		|| (c >= 'A' && c <= 'Z') || (c == '_'))
		return (0);
	else
		return (1);
}