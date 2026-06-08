/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:04:29 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/08 17:06:15 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void fill_map(t_parsing *parsing, t_list *map_lst)
{
	t_list	*tmp;
	int		i;

	parsing->map.grid = malloc(sizeof(char *) * (ft_lstsize(map_lst) + 1));
	tmp = map_lst;
	i = 0;
	while (tmp)
	{
		parsing->map.grid[i] = ft_strdup((char *)tmp->content); // enlever le \n?
		tmp = tmp->next;
		i++;
	}
	parsing->map.grid[i] = NULL;
	i = 0;
	while (parsing->map.grid[i])
	{
		printf("%s", parsing->map.grid[i]);
		i++;
	}
}
