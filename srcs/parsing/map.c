/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:14:05 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 13:00:23 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

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

int	check_map(t_parsing *parsing, int fd, char *line)
{
	t_list *map_lst = NULL;

	while (line)
	{
		parsing->map.width = max(parsing->map.width, (ft_strlen(line) - 1));
		parsing->map.height++;
		ft_lstadd_back(&map_lst, ft_lstnew(line));
		line = get_next_line(fd, 0);
	}
	fill_map(parsing, map_lst);
	ft_lstclear(&map_lst, free);
	if (!parse_map(parsing))
		return (get_next_line(fd, 1), printerr("Map error\n"), 0);
	if (!flood_fill(&parsing->map, parsing->player_x, parsing->player_y))
		return (get_next_line(fd, 1), printerr("Map is not closed\n"), 0);
	return (1);
}

int	set_player(t_parsing *parsing, int x, int y, char c)
{
	if (parsing->player_x != -1)
		return (printerr("Multiple player\n"), 0);
	parsing->player_x = x;
	parsing->player_y = y;
	parsing->player_orientation = c;
	return (1);
}

int	parse_chara(t_parsing *parsing, int x, int y)
{
	int	isok;

	isok = ft_forbidden(parsing->map.grid[y][x]);
	if (isok == 1 && !set_player(parsing, x, y, parsing->map.grid[y][x]))
		return (0);
	if (isok == 2)
		return (printerr("Forbidden character\n"), 0);
	if (isok == 3 && !check_door(parsing, x, y))
		return (0);
	if (isok == 4)
	{
		parsing->monster->pos.x = x;
		parsing->monster->pos.y = y;
	}
	return (1);	
}

int	parse_map(t_parsing *parsing)
{
	int	ndoors;
	int	nmonsters;

	ndoors = 0;
	nmonsters = 0;
	parsing->player_x = -1;
	count_entities(parsing, &ndoors, &nmonsters);
	if (ndoors)
		parsing->door = malloc(sizeof(t_door) * ndoors);
	if (nmonsters)
		parsing->monster = malloc(sizeof(t_monster) * nmonsters);
	if ((ndoors && !parsing->door) || (nmonsters && !parsing->monster))
		return (printerr("Malloc error\n"), 0);
	ndoors = -1;
	while (parsing->map.grid[++ndoors])
	{
		nmonsters = -1;
		while (parsing->map.grid[ndoors][++nmonsters])
			if (!parse_chara(parsing, nmonsters, ndoors))
				return (0);
	}
	if (parsing->player_x == -1)
		return (printerr("No player\n"), 0);
	return (1);
}
