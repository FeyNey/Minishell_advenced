/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:16:34 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/21 17:22:11 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	bt_u(char *l, t_bag **bag)
{
	int		j;
	char	*l_child;
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	j = end_tok(l);
	l_child = word_dup(l, 0, j);
	new->value = split_input(l_child);
	new->type = type_tok(new->value[0], (*bag)->env);
	new->next = 0;
	new->fdin = 0;
	new->fdout = 0;
	ft_addb_tok(&((*bag)->tokens), new);
	return (j);
}

//valeur de retour pour l'erreur int ?

static void	clean_tok(t_token **tok, t_env **env, t_bag **bag)
{
	t_token	*tmp;

	tmp = *tok;
	remove_redir(&(*bag)->tokens);
	while ((*tok))
	{
		replace_venv1(*tok, env, (*tok)->value);
		remove_quote(tok);
		(*tok) = (*tok)->next;
	}
	*tok = tmp;
}

void	printtok(t_token **t)
{
	int		i;
	t_token	*tmp;

	tmp = *t;
	while (tmp)
	{
		i = 0;
		printf(MAGENTA "\n || Token ||" RESET "\n");
		while (tmp->value[i])
		{
			printf("value[%i] %s\n", i, tmp->value[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
//		printf("type %d\n",tmp->type);

void	build_tokens(char *line, t_bag **bag)
{
	int	i;

	i = 0;
	if (!ft_verif_line(line))
		return ;
	while (line[i] && i < ft_strlen(line))
	{
		while (is_white(line[i]))
			i++;
		if (line[i])
			i += bt_u(&line[i], bag);
	}
	printf(CYAN "\nAvant Clean" RESET);
	printtok(&(*bag)->tokens);
	clean_tok(&((*bag)->tokens), &((*bag)->env), bag);
	printf(CYAN "\nApres Clean" RESET);
	printtok(&(*bag)->tokens);
}
