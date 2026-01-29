/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 07:20:37 by adeflers          #+#    #+#             */
/*   Updated: 2025/04/29 07:47:53 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*src;

	src = (unsigned char *)(s);
	i = 0;
	while (i < n)
	{
		if (src[i] == (unsigned char)(c))
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*
int	main()
{
	char s[] = "0000*000*00";
	char c = '*';

	printf("%s\n", ft_memchr(s, c, 9));
	return (0);
}
*/
