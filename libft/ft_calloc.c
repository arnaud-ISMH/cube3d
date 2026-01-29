/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:28:57 by adeflers          #+#    #+#             */
/*   Updated: 2025/04/30 21:51:09 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*str;
	size_t			i;

	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
/*
int	main()
{
	char *str = ft_calloc(8, 1);
	printf("%s\n", str);
	free(str);
	return (0);
}
*/
