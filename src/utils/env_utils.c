/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:59:27 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/20 09:47:13 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*e;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
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

void	ft_delnode_idx(t_env **lst, int idx)
{
	t_env	*temp;
	t_env	*flag;
	int		i;

	i = 0;
	if (lst == NULL || *lst == NULL)
		return ;
	flag = NULL;
	temp = *lst;
	while (i++ < idx)
	{
		flag = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	if (!flag)
		*lst = (*lst)->next;
	else
		flag->next = temp->next;
	free(temp->value);
	free(temp->key);
	free(temp);
	ft_indexion(*lst);
}
