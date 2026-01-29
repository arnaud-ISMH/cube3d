/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:11:15 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/05 17:33:23 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && (i + j) < len)
			{
				j++;
				if (little[j] == '\0')
					return ((char *)(big + i));
			}
		}
		i++;
	}
	return (NULL);
}
/*
int	main(int ac, char **av)
{
	char	*str = ft_strnstr(av[1], av[2], 89);
	char	*test = NULL;
	printf("%s\n", str);
	return 0;
}
*/
