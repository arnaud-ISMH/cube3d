/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:29:38 by adeflers          #+#    #+#             */
/*   Updated: 2025/06/06 19:29:38 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atoi_hexa(const char *nptr)
{
	int				i;
	unsigned int	result;

	i = 0;
	result = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	while ((nptr[i] >= '0' && nptr[i] <= '9')
		|| (nptr[i] >= 'a' && nptr[i] <= 'f')
		|| (nptr[i] >= 'A' && nptr[i] <= 'F'))
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			result = result * 16 + (nptr[i++] - '0');
		if (nptr[i] >= 'a' && nptr[i] <= 'f')
			result = result * 16 + (nptr[i++] - 'a' + 10);
		if (nptr[i] >= 'A' && nptr[i] <= 'F')
			result = result * 16 + (nptr[i++] - 'A' + 10);
	}
	return (result);
}

/* #include <stdio.h> */
/**/
/* int	main(int ac, char **av) */
/* { */
/* 	printf("%x\n", ft_atoi_hexa(av[1])); */
/* 	return (0); */
/* } */
