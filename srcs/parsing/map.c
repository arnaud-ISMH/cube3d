/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:14:05 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/09 18:21:17 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	flood_fill(t_map *map, int x, int y) //D = mur, X= traversable?
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'X')
		return (1);
	map->grid[y][x] = 'X'; 
	return (flood_fill(map, x + 1, y) && flood_fill(map, x - 1, y) &&
			flood_fill(map, x, y + 1) && flood_fill(map, x, y - 1)); //renvoie 1 si tout renvoie 1
}

int	ft_forbidden(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == 'D')
		return (3);
	if (c == 'X')
		return (4);
	return (2);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	free(*lst);
	*lst = NULL;
}

int	check_map(t_parsing *parsing, int fd, char *line)
{
	int player = 0;
	int isok;
	int i;
	t_list *map_lst = NULL;

	while (line)
	{
		parsing->map.width = max(parsing->map.width, (ft_strlen(line) - 1));
		parsing->map.height++;
		// printf("width %i, height %i, isok %i\n", parsing->map.width, parsing->map.height, isok);
		i = 0;
		while (line[i] != '\n' && line[i] != '\0') 
		{
			isok = ft_forbidden(line[i]);
			if (isok == 1)
			{
				if (player)
					return (free(line), get_next_line(fd, 1), ft_lstclear(&map_lst, free), printerr("Multiple player\n"), 0);
				else
				{
					parsing->player_x = i;
					parsing->player_y = parsing->map.height - 1;
					parsing->player_orientation = line[i];
					player = 1;
				}
			}
			if (isok == 2)
				return (free(line), get_next_line(fd, 1), ft_lstclear(&map_lst, free), printerr("Forbidden character\n"), 0);
			if (isok == 3)
				check_door(parsing, line, i); //creer map dabord?
			if (isok == 4)
				new_monster(parsing, line, i); //ca ok chill
			i++;
		}
		ft_lstadd_back(&map_lst, ft_lstnew(line)); //free line pas poss sinon jperds mon content? securiser le lstnew?
		line = get_next_line(fd, 0);
	}
	if (!player)
		return (free(line), get_next_line(fd, 1), ft_lstclear(&map_lst, free), printerr("No player\n"), 0);
	fill_map(parsing, map_lst);
	ft_lstclear(&map_lst, free);
	if (!flood_fill(&parsing->map, parsing->player_x, parsing->player_y))
		return (get_next_line(fd, 1), printerr("Map is not closed\n"), 0); //free parsing ?
	return (1);
}
