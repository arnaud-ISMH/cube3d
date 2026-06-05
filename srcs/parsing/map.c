/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:14:05 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/05 16:57:45 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	flood_fill(t_map *map, int x, int y)
{
	//tout modifier en parsing->
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'X')
		return (1); // Mur ou déjà visité
	map->grid[y][x] = 'X'; //  visité
	// Vérifier les quatre directions
	return (flood_fill(map, x + 1, y) && flood_fill(map, x - 1, y) &&
			flood_fill(map, x, y + 1) && flood_fill(map, x, y - 1)); //renvoie 1 si tout renvoie 1
}

int	ft_forbidden(char c)
{
	if (c == '0' || c == '1' || c == ' ') //32 dans la map? 32 devient sol
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (2);
}

int	check_map(t_parsing *parsing, int fd, char *line)
{
	int player = 0;
	int isok = 0;
	int i;
	t_list *map_lst = NULL;

	while (line)
	{
		// printf("line = '%s\n'", line);
		parsing->map.width = max(parsing->map.width, (ft_strlen(line) - 1));
		parsing->map.height++;
		// printf("width %i, height %i, isok %i\n", parsing->map.width, parsing->map.height, isok);
		i = 0;
		while (line[i] != '\n' && line[i] != '\0') 
		{
			isok = ft_forbidden(line[i]); //32 ok si hors map
			if (isok == 1) //joueur
			{
				if (player)
					return (free(line), printerr("Multiple player\n"), 0);
				else
				{
					parsing->player_x = i;
					parsing->player_y = parsing->map.height - 1;
					parsing->player_orientation = line[i];
					player = 1;
				}
			}
			if (isok == 2)
				return (free(line), printerr("Forbidden character\n"), 0);
			i++;
		}
		ft_lstadd_back(&map_lst, ft_lstnew(line)); //free line pas poss sinon jperds mon content? securiser le lstnew?
		line = get_next_line(fd);
	}
	//PRINT LST
	// t_list *tmp;
	// tmp = map_lst;
	// free(line);
	// while (tmp)
	// {
	// 	printf("%s", (char *)tmp->content);
	// 	tmp = tmp->next;
	// }
	if (!player)
		return (printerr("No player\n"), 0);
	fill_map(parsing, map_lst);
	//ft_lstclear(&map_lst, free); //free lst
	if (!flood_fill(&parsing->map, parsing->player_x, parsing->player_y))
		return (printerr("Map is not closed\n"), 0); //free sturct, map
	return (1);
}
