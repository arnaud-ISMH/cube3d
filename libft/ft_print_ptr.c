/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:18:47 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/07 13:43:53 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size(unsigned long long ptr)
{
	unsigned int	size;

	size = 0;
	while (ptr != 0)
	{
		size++;
		ptr = ptr / 16;
	}
	return (size);
}

static void	ft_putnbr_ptr(unsigned long long ptr)
{
	if (ptr >= 16)
	{
		ft_putnbr_ptr(ptr / 16);
		ft_putnbr_ptr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar_fd((ptr + '0'), 1);
		else
			ft_putchar_fd((ptr - 10 + 'a'), 1);
	}
}

int	ft_print_ptr(unsigned long long ptr)
{
	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	ft_putnbr_ptr(ptr);
	return (size(ptr) + 2);
}
