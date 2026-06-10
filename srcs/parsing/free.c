/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:36:44 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/10 13:59:57 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	free_parsing(t_parsing *parsing)
{
	if (!parsing)
		return ;
	free(parsing->no);
	free(parsing->so);
	free(parsing->we);
	free(parsing->ea);
	if (parsing->map.grid)
		freefree(parsing->map.grid);
	free(parsing->monster);
	free(parsing->door);
	free(parsing);
}

char	**freefree(char **split)
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