/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:12:40 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/07 10:35:59 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	siz(unsigned int n)
{
	unsigned int	count;
	unsigned int	nbr;

	count = 0;
	nbr = n;
	while (nbr > 0)
	{
		count++;
		nbr = nbr / 10;
	}
	if (count == 0)
		count++;
	return (count);
}

static int	pw(unsigned int nb, unsigned int pui)
{
	unsigned int	i;
	unsigned int	res;

	if (pui == 0)
		return (1);
	i = 0;
	res = nb;
	while (i < pui - 1)
	{
		res *= nb;
		i++;
	}
	return (res);
}

static char	*process(unsigned int n, char *res)
{
	unsigned int	nbr;
	unsigned int	i;
	unsigned int	t1;
	unsigned int	t2;

	i = 0;
	nbr = n;
	while (i < siz(n))
	{
		res[i++] = nbr / pw(10, (siz(nbr) - 1)) + '0';
		t1 = siz(nbr);
		nbr = nbr % pw(10, (siz(nbr) - 1));
		t2 = siz(nbr) - 1;
		while (++t2 < t1 - 1)
			res[i++] = '0';
	}
	res[i] = '\0';
	return (res);
}

static char	*utoa(unsigned int n)
{
	char	*res;

	res = malloc(sizeof(char) * (siz(n) + 1));
	if (!res)
		return (NULL);
	return (process(n, res));
}

int	ft_print_unsigned(unsigned int nbr)
{
	char	*nb;
	int		size;

	nb = utoa(nbr);
	size = ft_print_str(nb);
	free(nb);
	return (size);
}
