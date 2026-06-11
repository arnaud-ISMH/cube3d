/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:04:29 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 12:58:31 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void fill_map(t_parsing *parsing, t_list *map_lst)
{
	t_list	*tmp;
	int		i;
	int		len;

	tmp = map_lst;
	i = 0;
	parsing->map.grid = malloc(sizeof(char *) * (ft_lstsize(map_lst) + 1));
	while (tmp)
	{
        parsing->map.grid[i] = malloc(parsing->map.width + 1);
        len = ft_strlen((char *)tmp->content);
        if (len > 0 && ((char *)tmp->content)[len - 1] == '\n')
            len--;
        // copie la ligne sans \n
        ft_memcpy(parsing->map.grid[i], tmp->content, len);
        // pad le reste avec des espaces
        ft_memset(parsing->map.grid[i] + len, ' ', parsing->map.width - len);
		parsing->map.grid[i][parsing->map.width] = '\0';
		tmp = tmp->next;
		i++;
	}
	parsing->map.grid[i] = NULL;
	i = 0; //reprint map a del
	while (parsing->map.grid[i])
	{
		printf("[%s]\n", parsing->map.grid[i]);
		i++;
	}
}
