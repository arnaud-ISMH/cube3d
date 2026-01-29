/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:44:28 by adeflers          #+#    #+#             */
/*   Updated: 2025/04/29 02:27:59 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (dst[i] && i <= siz)
		i++;
	while (src[j])
		j++;
	if (siz <= i)
		return (siz + j);
	while (src[k] && k < (siz - 1 - i))
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = '\0';
	return (i + j);
}
/*
int	main()
{
	char	s[] = "0000000000";
	char	d[] = "1111111111";
	size_t	a;

	printf("%s\n", s);
	printf("%s\n", d);
	printf("%zu\n", a);

	a = ft_strlcat(d, s, 13);

	printf("%s\n", s);
	printf("%s\n", d);
	printf("%zu\n", a);
}
*/
