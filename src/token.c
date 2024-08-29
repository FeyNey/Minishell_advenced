/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:16:34 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/29 16:31:48 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bt_u(char *l, t_bag **bag)
{
	int		j;
	char	*l_child;
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	j = end_tok(l);
//	printf("end token %d\n",j);
	l_child = word_dup(l, 0, j);
//	printf("l_child %s\n",l_child);
	new->value = split_input(l_child);
	free(l_child);
	new->type = type_tok(new->value[0], (*bag)->env); //verif pas bon
	new->next = 0;
	ft_addb_tok(&((*bag)->tokens), new);
	return (j);
}

void	printtok(t_token **t)
{
	t_token	*temp;
	int i;

	temp = *t;
	while (temp)
	{
		printf("\nTOKEN\n");
		i = 0;
		while (temp->value[i])
		{
			printf("value [%i] %s\n", i, temp->value[i]);
			i++;
		}
//		printf("type %d\n", temp->type);
		temp = temp->next;
	}
	printf("\n");
}

void	build_tokens(char *line, t_bag **bag)
{
	int	i;

	i = 0;
	while (line[i] && i < ft_strlen(line))
	{
		while (is_white(line[i]))
			i++;
		if (line[i])
			i += bt_u(&line[i], bag);
	}
	printtok(&(*bag)->tokens);
}
