/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triple_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:32:52 by acoste            #+#    #+#             */
/*   Updated: 2024/08/23 19:39:19 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strcpy(char *str, char *dest)
{
	int	id;

	id = 0;
	while (str[id])
	{
		dest[id] = str[id];
		id += 1;
	}
	dest[id] = '\0';
}

char	*ft_strjoin_t(char *strt, char *mid, char *end)
{
	int		i;
	int		nb_char;
	char	*new_str;

	if (!strt || !mid || !end)
		return (0);
	nb_char = (ft_strlen(strt) + ft_strlen(end) + ft_strlen(mid));
	new_str = malloc(sizeof(char) * (nb_char + 1));
	if (!new_str)
		return (0);
	i = 0;
	ft_strcpy(strt, &new_str[i]);
	i = ft_strlen(new_str);
	ft_strcpy(mid, &new_str[i]);
	i = ft_strlen(new_str);
	ft_strcpy(end, &new_str[i]);
	return (new_str);
}
