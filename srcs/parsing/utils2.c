/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:08:00 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 13:46:51 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	strip(char *s)
{
	char *res;

	res = ft_strchr(s, '\n');
	if (res)
		*res = '\0';
}

int ft_isnumber(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] < 48 || line[i] > 57)
			return (0);
		i++;
	}
	return (1);
}
