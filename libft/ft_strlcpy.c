/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:15:37 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/05 17:51:20 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (src[j])
		j++;
	if (siz == 0)
		return (j);
	i = 0;
	while (src[i] && i < siz - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}
/*
int	main()
{
	char	s[] = "123456789";
	char	d[] = "000";
	size_t	a;

	printf("%s\n", s);
	printf("%s\n", d);
	printf("%zu\n", a);

	a = ft_strlcpy(d, s, 7);

	printf("%s\n", s);
	printf("%s\n", d);
	printf("%zu\n", a);
}
*/
