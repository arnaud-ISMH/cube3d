/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:41:41 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/07 12:17:34 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_size(unsigned int n)
{
	unsigned int	size;

	size = 0;
	while (n != 0)
	{
		size++;
		n = n / 16;
	}
	return (size);
}

static void	ft_putnbr_hexa(unsigned int n, const char format)
{
	if (n >= 16)
	{
		ft_putnbr_hexa(n / 16, format);
		ft_putnbr_hexa(n % 16, format);
	}
	else
	{
		if (n <= 9)
			ft_putchar_fd((n + '0'), 1);
		else
		{
			if (format == 'x')
				ft_putchar_fd((n - 10 + 'a'), 1);
			if (format == 'X')
				ft_putchar_fd((n - 10 + 'A'), 1);
		}
	}
}

int	ft_print_hexa(unsigned int n, const char format)
{
	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	ft_putnbr_hexa(n, format);
	return (hex_size(n));
}
