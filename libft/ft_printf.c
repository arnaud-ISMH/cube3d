/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 05:34:41 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/14 19:53:12 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(va_list args, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_print_char(va_arg(args, int));
	else if (format == 's')
		count += ft_print_str(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		count += ft_print_nbr(va_arg(args, int));
	else if (format == '%')
		count += ft_print_percent();
	else if (format == 'u')
		count += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_print_hexa(va_arg(args, unsigned int), format);
	else if (format == 'p')
		count += ft_print_ptr((unsigned long long)va_arg(args, void *));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!str)
		return (-1);
	count = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += ft_format(args, str[i + 1]);
			i++;
		}
		else
			count += ft_print_char(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
