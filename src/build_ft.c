/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:59:27 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/29 17:52:44 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*e;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		e = ft_lstlast(*lst);
		e->next = new;
		ft_indexion(*lst);
	}
}

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*l;

	l = (t_env *)malloc(sizeof(t_env));
	if (!l)
		return (NULL);
	l->key = ft_strdup(key);
	l->value = ft_strdup(value);
	l->index = 0;
	l->next = NULL;
	return (l);
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_delnode_key(t_env **lst, char *key )
{
	t_env	*temp;
	t_env	*flag;

	if (lst == NULL || *lst == NULL)
		return ;
	flag = NULL;
	temp = *lst;
	while (temp && ft_cmp(temp->key, key) == 0)
	{
		flag = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	if (!flag)
		*lst = (*lst)->next;
	else if (temp->next)
		flag->next = temp->next;
	else if (!temp->next)
		flag->next = NULL;
	free(temp);
	ft_indexion(*lst);
}

void	ft_indexion(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list->index = i;
		list = list->next;
		i++;
	}
}
