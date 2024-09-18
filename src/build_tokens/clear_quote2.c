/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:00:59 by alexis            #+#    #+#             */
/*   Updated: 2024/09/18 15:59:33 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// void	clear_token(t_token **tok, t_env **env) // valeur de retour pour l erreur ?
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = tok_len(tok);
// 	while (i < j)
// 	{
// 		replace_$(*tok, env, (*tok)->value); //verif
// 		supp_quote(tok, (*tok)->value); //verif
// 		(*tok) = (*tok)->next;
// 		i++;
// 	}
// }

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
			new = replace_$2(tok->value[j], env);
			tok->value[j] = new;
		}
		else
			j++;
		//return ;
	}
}

int	is_between_quote_and_has_$(char *word)
{
	int i;
	int f;
	char prev;

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
		if (word[i] == '$' && prev != 92)
			f = 1;
		prev = word[i];
		i++;
	}
	if (f == 1)
		return (1);
	else
		return (0);
}

int not_between_quote(char *str, char c, int j)
{
	int i;

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

char *replace_$2(char *str, t_env **env)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] != '$' && str[i])
			i++;
		if (str[i] == '$')
		{
			j = i + 1;
			while ((is_env_char(str[j]) == 0) && (str[j]))
				j++;
			new = replace_$3(str, env, i, j);
			str = new;
			i = 0;
			printf(CYAN "\nMid Clean\n" RESET);
			printf("%s\n", str);
			//return(0);
		}
	}
	return (new);
}

char *replace_$3(char *str, t_env **env, int i, int j)
{
	char *new;
	int f;

	f = is_in_ev_tok(str + i + 1, *env);
	if (f >= 0)
	{
		new = replace_venv(str, i, j, found_in_env(env, f));
		printf(CYAN "\n\n replace venv\n\n" RESET);
	}
	if (f == -1)
	{
		new = skip_venv(str, i, j);
		printf(CYAN "\n\n skip venv\n\n" RESET);
	}
	free(str);
	return (new);
}

char *found_in_env(t_env **env, int index)
{
//	t_env *tmp;
	int i;

	i = 0;
	while (i < index)
	{
		(*env) = (*env)->next;
		i++;
	}
	return ((*env)->value);
}

char	*skip_venv(char *str, int i, int j)
{
	int x;
	int y;
	char *new;

	x = 0;
	y = 0;
	printf("i : %i\n", i);
	printf("j : %i\n", j);
	printf("str : %i\n", ft_strlen(str));
	printf("skip venv malloc size of : %i\n", ft_strlen(str) - (j - i));
	new = ft_malloc(ft_strlen(str) - (j - i));
	new[ft_strlen(str) - j] = '\0';
	while (str[x] != '$')
	{
		new[y] = str[x];
		y++;
		x++;
	}
	x++;
	while (is_env_char(str[x]) == 0)
		x++;
	while (str[x])
	{
		new[y] = str[x];
		y++;
		x++;
	}
	new[y] = '\0';
	return (new);
}
char	*replace_venv(char *str, int i, int j, char *value)
{
	int x;
	int y;
	int diff;
	char *new;

	x = 0;
	diff = (j - i);
	printf("i : %i\n", i);
	printf("j : %i\n", j);
	printf("str : %i\n", ft_strlen(str));
	printf("value : %i\n", ft_strlen(value));
	printf(YELLOW "replace venv malloc size of : %i\n" RESET, (ft_strlen(str) + ft_strlen(value) - (j - i)));
	new = ft_malloc((ft_strlen(str) + ft_strlen(value) - (j - i)));
	new[(ft_strlen(str) - j) + (ft_strlen(value))] = '\0';
	i = 0;
	y = 0;
	while (str[i] != '$')
	{
		new[y] = str[i];
		i++;
		y++;
	}
	while (value[x])
	{
		new[y] = value[x];
		y++;
		x++;
	}
	i = i + diff;
	printf(RED "%i\n" RESET, i);
	while (str[i])
	{
		new[y] = str[i];
		y++;
		i++;
	}
	new[y] = '\0';
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

int	is_in_ev_tok(char *arg, t_env *myev)
{
	char	*k;
	int		flag;
	int		targ;

	targ = 0;
	flag = 0;
	while (is_env_char(arg[flag]) == 0)
		flag++;
	// if (flag == 0)
	// 	return (-1);
	k = word_dup(arg , 0, flag);
	while (myev)
	{
		if (!ft_cmp(myev->key, k))
		{
			if (flag >= 0)
				free(k);
			return (targ);
		}
		targ++;
		myev = myev->next;
	}
	if (k)
		free(k);
	return (-1);
}