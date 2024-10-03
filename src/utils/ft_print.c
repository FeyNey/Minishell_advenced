/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:52:07 by acoste            #+#    #+#             */
/*   Updated: 2024/10/03 16:02:06 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	putnbr_base(long nb, char *base)
{
	int	i;
	int	value;

	value = 0;
	i = 0;
	while (base[i])
		i++;
	if (nb < 0)
	{
		write(1, "-", 1);
		value++;
		nb = nb * -1;
	}
	if (nb >= i)
	{
		value += putnbr_base(nb / i, base);
		value += ft_putchar(base[nb % i]);
	}
	else
	{
		value += ft_putchar(base[nb % i]);
	}
	return (value);
}

int	unsigned_putnbr_base(unsigned int nb, char *base)
{
	unsigned int	i;
	int				value;

	value = 0;
	i = 0;
	while (base[i])
		i++;
	if (nb >= i)
	{
		value += putnbr_base(nb / i, base);
		value += ft_putchar(base[nb % i]);
	}
	else
	{
		value += ft_putchar(base[nb % i]);
	}
	return (value);
}

int	longlong_putnbr_base(unsigned long long nb, char *base, int j)
{
	unsigned long long	i;
	int					value;

	if (nb == 0)
		return (write(1, "(nil)", 5));
	value = 0;
	i = 0;
	if (j == 0)
	{
		ft_putstr("0x");
		value = value + 2;
	}
	while (base[i])
		i++;
	if (nb >= i)
	{
		value += longlong_putnbr_base(nb / i, base, 1);
		value += ft_putchar(base[nb % i]);
	}
	else
		value += ft_putchar(base[nb % i]);
	return (value);
}
