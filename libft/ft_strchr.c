/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:53:47 by adeflers          #+#    #+#             */
/*   Updated: 2025/04/29 05:45:02 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)(c))
			return ((char *)s);
		s++;
	}
	if ((char)(c) == '\0')
		return ((char *)s);
	return (NULL);
}
/*
int	main()
{
	char	s[] = "0*1-2?3:4!5&0*1-2?3:4!5";
	char	c = '!';
	char	*res;

	res = ft_strchr(s, c);
	printf("%s\n", res);
	return (0);
}
*/
