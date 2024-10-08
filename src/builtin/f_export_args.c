/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:28:06 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/26 17:35:10 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	add_myenv(char	*arg, t_env **myenv)
{
	char	**constr;
	t_env	*new;

	if (find_c(arg, '=') > -1)
	{
		constr = constructor(arg);
		new = ft_lstnew(constr[0], constr[1]);
		ft_free_split(constr);
	}
	else
		new = ft_lstnew(arg, "\0");
	ft_lstadd_back(myenv, new);
}

int	is_in_ev(char *arg, t_env *myev)
{
	char	*k;
	int		flag;
	int		targ;

	targ = 0;
	flag = ft_strlen(arg);
	if (find_c(arg, '=') != -1)
		flag = find_c(arg, '=');
	k = word_dup(arg, 0, flag);
	while (myev)
	{
		if (!ft_cmp(myev->key, k))
		{
			free(k);
			return (targ);
		}
		targ++;
		myev = myev->next;
	}
	free(k);
	return (-1);
}

static void	srch_replace(t_env **menv, int id, char *arg)
{
	t_env	*tmp;
	char	**constr;

	if ((find_c(arg, '=')) == -1)
		return ;
	constr = constructor(arg);
	tmp = (*menv);
	while (tmp->index != id)
		tmp = tmp->next;
	free(tmp->key);
	free(tmp->value);
	tmp->key = ft_strdup(constr[0]);
	tmp->value = ft_strdup(constr[1]);
	ft_free_split(constr);
}

/* 'valable' selon export soit verif ur 1er caracter
 diff de chiff ou _ puis etre que des chiffre ou des _*/
static int	env_valable(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if ((arg[0] >= 48 && arg[0] <= 57) || (arg[0] == 95 && !arg[1]))
		return (0);
	while (arg[i])
	{
		if (arg[i] >= 65 && arg[i] <= 90)
			i++;
		else if (arg[i] >= 97 && arg[i] <= 122)
			i++;
		else if (arg[i] >= 48 && arg[i] <= 57)
			i++;
		else if (arg[i] == 95)
			i++;
		else if (arg[i] == '=')
			break ;
		else
			return (0);
	}
	return (1);
}

int	export_args(t_token *ts, t_env **myev, int i)
{
	int	id_targ;

	while (ts->value[i])
	{
		if (!(env_valable(ts->value[i])))
			printf("export: << %s >> : id non valable\n", ts->value[i]);
		else
		{
			id_targ = is_in_ev(ts->value[i], (*myev));
			if (id_targ >= 0)
				srch_replace(myev, id_targ, ts->value[i]);
			else
				add_myenv(ts->value[i], myev);
		}
		i++;
	}
	return (0);
}
