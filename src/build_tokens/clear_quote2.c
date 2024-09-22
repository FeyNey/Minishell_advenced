/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:00:59 by alexis            #+#    #+#             */
/*   Updated: 2024/09/22 16:35:46 by acoste           ###   ########.fr       */
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
	int		i;

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
		if ((word[i] == '$') && (prev != 92) && (is_env_char2(word[i + 1]) == 0))
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
			break;
		if (str[i] == '$')
		{
			j = i + 1;
			while ((is_env_char(str[j]) == 0) && (str[j]))
				j++;
			new = replace_venv3(str, env, i, j);
			str = new;
			i = 0;
			printf(CYAN "\nMid Clean\n" RESET);
			printf("%s\n", str);
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
		printf(CYAN "\n\n replace venv\n\n" RESET);
	}
	else if (f == -1)
	{
		new = skip_venv(str, i, j);
		printf(CYAN "\n\n skip venv\n\n" RESET);
	}
	// else if (??)
	// {
		// new = word_dup(str, 0, ft_strlen(str));
	// }
	free(str);
	return (new);
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

char	*skip_venv(char *str, int i, int j)
{
	int		x;
	int		y;
	char	*new;
	char	*stock;

	x = 0;
	y = 0;
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
	new = ft_malloc(ft_strlen(str) - (j - i));
	while (x < is_valable_venv(str))
		new[y++] = str[x++];
	if (is_env_char(str[x + 1] == 1))
		new[y++] = str[x++];
	while (is_env_char(str[x]) == 0 && str[x])
		x++;
	while (str[x])
		new[y++] = str[x++];
	new[y] = '\0';
	return (new);
}

char *number_venv(char *str, int i)
{
	char *new;
	int y;

	if (str[i + 1] == '0')
		return(replace_venv4(str, i, i + 2, "minishell"));
	else
	{
		y = 0;
		new = ft_malloc(ft_strlen(str) - 2);
		i = 0;
		while (i < is_valable_venv(str))
		{
			new[y] = str[i];
			i++;
			y++;
		}
		i = i + 2;
		while (str[i])
		{
			new[y] = str[i];
			i++;
			y++;
		}
	}
	return (new);
}

char	*replace_venv4(char *str, int i, int j, char *value)
{
	int		x;
	int		y;
	int		diff;
	char	*new;

	x = 0;
	// printf("replace venv i : %i\n", i);
	diff = (j - i);
	new = ft_malloc((ft_strlen(str) + ft_strlen(value) - (j - i)));
	new[(ft_strlen(str) - j) + (ft_strlen(value))] = '\0';
	i = 0;
	y = 0;
	while (i < is_valable_venv(str))
	{
		new[y] = str[i];
		i++;
		y++;
	}
	// printf("replace venv y : %i\n", y);
	while (value[x])
	{
		new[y] = value[x];
		y++;
		x++;
	}
	i = i + diff;
	while (str[i])
	{
		new[y] = str[i];
		y++;
		i++;
	}
	new[y] = '\0';
	return (new);
}

int	is_env_char(char c)
{
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
	else if(c == ' ')
		return (1);
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')
		|| (c >= '0' && c <= '9') || (c == '-') || (c == '$'))
		return (0);
	else
		return (1);
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
