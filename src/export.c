/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:28:06 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/26 17:35:10 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in(int idx, int *tri)
{
	int	i;

	i = 0;
	while (tri[i] != -1) 
	{ 
		if (tri[i] == idx)
			return 1;
		i++;
	}
	return 0;
}

int	add_myenv(t_token *toks, t_env **myenv) 
{
	(void)toks;
	(void)*myenv;
	printf("have to do\n");
	return (0);
}

static void	add_croiss(t_env *e, int *tri)
{
	t_env	*min;
	t_env	*compare;
	int		i;

	i = 0;
	min = e;
	while (min)
	{
		compare = min->next;
		while (compare)
		{
			if (!(is_in(compare->index, tri)) && ft_cmp(min->key, compare->key) > 0)
				min = compare;
			compare = compare->next;
		}
		tri[i] = min->index;
		i++;
		min = e;
		while (min && is_in(min->index, tri))
			min = min->next;
	}
}

static int      w_export(t_env *myenv)
{
        write(1, "declare -x ", 11);
        write(1 ,myenv->key, ft_strlen(myenv->key));
        if (myenv->value != NULL)
	{
		write(1 , "=\"", 2);
                write(1 ,myenv->value, ft_strlen(myenv->value));
		write(1 , "\"", 1);
	}
        write(1, "\n", 1);
        return (0);
}

static void	write_croiss(t_env *e, int *order)
{
	int		i;
	t_env	*temp;

	i = 0;
	while (order[i])
	{
		temp = e;
		while (temp->index != order[i])
			temp = temp->next;
		w_export(temp);
		i++;
	}
}

int	build_export(t_env *e)
{
	int	*ordo;
	int	i;

	i = (ft_lstlast(e))->index;
	ordo = malloc(sizeof(int) * (i + 2));
	ordo[i + 1] = -1;
	add_croiss(e, ordo);
	write_croiss(e, ordo);
	free(ordo);
	return (0);
}
