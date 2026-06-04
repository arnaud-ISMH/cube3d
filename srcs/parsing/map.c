/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:14:05 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/04 17:49:50 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	flood_fill(t_map *map, int x, int y)
{
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

int	check_map(t_parsing *parsing, int fd)
{
	int player = 0;
	int isok = 0;
	int i;
	char *line;
	// t_list *map_list = NULL;
	line = get_next_line(fd); //a securiser
	while (line) //idem recup premiere
	{
		printf("line = '%s'", line);
		parsing->map.width = max(parsing->map.width, (ft_strlen(line) - 1));
		parsing->map.height++;
		printf("width %i, height %i, isok %i\n", parsing->map.width, parsing->map.height, isok);
		i = 0;
		while (line[i] != '\n') 
		{
			printf("caractere = %c\n", line[i]);
			isok = ft_forbidden(line[i]); //32 ok si hors map
			printf("seg?\n");
			if (isok == 1) //joueur
			{
				if (player)
					return (printerr("Multiple player\n"), 0);
				else
				{
					parsing->player_x = i;
					parsing->player_y = parsing->map.height - 1;
					parsing->player_orientation = line[i];
					player = 1;
				}
			i++;
			}
			if (isok == 2)
				return (printerr("Forbidden character\n"), 0);
			free(line);
			line = get_next_line(fd);
		}
		// recup line dans lst //lst_add_back(&map_list, line);
		// next_line;
	}
	//free(line);
	// if (!flood_fill(&parsing->map, parsing->player_x, parsing->player_y))
	// 	return (printerr("Map is not closed\n"), 0);
	if (!player)
		return (printerr("No player\n"), 0);
	// fill_map(parsing, map_list); //remplir la map avec la lst
	return (1);
}
