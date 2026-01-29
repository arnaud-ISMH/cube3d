/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 02:02:54 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/02 20:43:57 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	taille(char const *str, char const charset)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != charset)
		i++;
	return (i);
}

static int	count_w(char const *s, char charset)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == charset)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != charset)
				i++;
		}
	}
	return (count);
}

static char	*couped(char const *str, char c)
{
	char	*couped;
	int		i;

	i = 0;
	couped = malloc(sizeof(char) * (taille(str, c) + 1));
	if (!couped)
		return (NULL);
	while (i < taille(str, c))
	{
		couped[i] = str[i];
		i++;
	}
	couped[i] = '\0';
	return (couped);
}

static char	**setfree(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		size;
	int		i;
	int		j;

	size = count_w(s, c);
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < size)
	{
		while (s[i] == c)
			i++;
		result[j] = couped(&s[i], c);
		if (result[j] == NULL)
			return (setfree(result));
		i = i + taille(result[j], c);
		j++;
	}
	result[j] = NULL;
	return (result);
}

/*
int	main()
{
	char	s[] = "  yo la team ";
	char	c = ' ';
	char	**split;
	int	i;

	i = 0;
	split = ft_split(s, c);
	while (split[i])
	{
		printf(">%s<\n", split[i]);
		free(split[i]);
		i++;
	}
	printf("%s\n", split[i]);
	free(split);
	return (0);
}
*/
