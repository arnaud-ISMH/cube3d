/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:36:44 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/09 16:07:56 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	free_parsing(t_parsing *parsing)
{
	// int i;

	if (!parsing)
		return ;
	free(parsing->no);
	free(parsing->so);
	free(parsing->we);
	free(parsing->ea);
	if (parsing->map.grid)
	{
		freefree(parsing->map.grid);
		// i = 0;
		// while (parsing->map.grid[i])
		// {
		// 	free(parsing->map.grid[i]);
		// 	i++;
		// }
		// free(parsing->map.grid);
	}
	free(parsing);
}

//freeesplit

	//PRINT LST
	// t_list *tmp;
	// tmp = map_lst;
	// free(line);
	// while (tmp)
	// {
	// 	printf("%s", (char *)tmp->content);
	// 	tmp = tmp->next;
	// }

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