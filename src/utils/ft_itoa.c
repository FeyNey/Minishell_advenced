/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:44:42 by acoste            #+#    #+#             */
/*   Updated: 2024/10/11 13:33:41 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_nbr(int nbr)
{
	int	i;

	i = 0;
	if (nbr == -2147483648)
		return (11);
	if (nbr < 0)
	{
		i++;
		nbr = nbr * (-1);
	}
	while (nbr > 9)
	{
		nbr = nbr / 10;
		i++;
	}
	i++;
	return (i);
}

static char	*cop(char *src, char *t)
{
	int	i;

	i = 0;
	while (src[i])
	{
		t[i] = src[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}

static char	*conv(int nbrn, int n, char *tab)
{
	int	i;

	i = 0;
	tab[nbrn] = '\0';
	nbrn--;
	if (n < 0)
	{
		tab[i] = '-';
		i++;
		n = n * (-1);
	}
	while (n > 9)
	{
		tab[nbrn] = (n % 10) + '0';
		n = n / 10;
		nbrn--;
	}
	tab[nbrn] = n + '0';
	return (tab);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;

	i = count_nbr(n);
	tab = (char *)malloc(sizeof(char) * i + 1);
	if (!tab)
		return (0);
	if (n == -2147483648)
		return (cop("-2147483648", tab));
	return (conv(i, n, tab));
}
