/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:35:24 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/05 21:50:19 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	taille(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	is_charset(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	nb_trim(char const *s1, char const *set)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s1[i] && is_charset(s1[i], set))
	{
		count++;
		i++;
	}
	if (count == taille(s1))
		return (count);
	i = taille(s1) - 1;
	while (s1[i] && is_charset(s1[i], set))
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed;
	int		i;
	int		j;
	int		k;

	trimed = malloc(sizeof(char) * (taille(s1) - nb_trim(s1, set) + 1));
	if (!trimed)
		return (NULL);
	i = 0;
	j = 0;
	k = taille(s1) - 1;
	while (s1[i] && is_charset(s1[i], set) == 1)
		i++;
	while (s1[k] && is_charset(s1[k], set) == 1)
		k--;
	while ((i + j) <= k)
	{
		trimed[j] = s1[i + j];
		j++;
	}
	trimed[j] = '\0';
	return (trimed);
}
/*
int	main()
{
	char	s1[] = "aaaaa";
	char	set[] = "a";
	char	*trim;

	trim = ft_strtrim(s1, set);

	printf("%s\n", trim);
	free(trim);
	return (0);
}
*/
