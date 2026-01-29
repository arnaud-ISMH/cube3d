/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:34:34 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/05 23:33:38 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	siz(long n)
{
	int		count;
	long	nbr;

	count = 0;
	nbr = n;
	if (nbr < 0)
	{
		count++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		count++;
		nbr = nbr / 10;
	}
	if (count == 0)
		count++;
	return (count);
}

static int	pw(int nb, int pui)
{
	int	i;
	int	res;

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

static char	*process(int n, char *res)
{
	unsigned int	nbr;
	int				i;
	int				t1;
	int				t2;

	i = 0;
	if (n < 0)
	{
		nbr = -n;
		res[i++] = '-';
	}
	else
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

char	*ft_itoa(int n)
{
	char	*res;

	res = malloc(sizeof(char) * (siz(n) + 1));
	if (!res)
		return (NULL);
	return (process(n, res));
}
/*
int	main(int ac, char **av)
{
	char *test;
	
	test = ft_itoa(atoi(av[1]));
	printf("%s\n", test);
	free(test);
	return (0);
}
*/
