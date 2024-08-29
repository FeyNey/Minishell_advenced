/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:07:01 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/29 17:15:48 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft"

int	ft_strlen(char *s)
{
	int	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

void	ft_putnstr(char *str, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(1, &str[i], 1);
		i++;
	}
}