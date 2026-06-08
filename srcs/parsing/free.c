/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:36:44 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/08 17:06:08 by lchapot          ###   ########.fr       */
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
	/* free map.grid si allouée */
	if (parsing->map.grid)
	{
		int i = 0;
		while (parsing->map.grid[i])
		{
			free(parsing->map.grid[i]);
			i++;
		}
		free(parsing->map.grid);
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