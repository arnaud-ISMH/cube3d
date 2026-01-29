/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:21:33 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/07 07:03:50 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	while (j < i)
	{
		f(j, &s[j]);
		j++;
	}
}
/*
void	testeur(unsigned int n, char *s)
{
	*s =  *s + n;
}

int	main()
{
	char s1[] = "AAAAA";

	printf("avant ft : %s\n\n", s1);
	ft_striteri(s1, testeur);
	printf("apres ft : %s\n\n", s1);

}
*/
