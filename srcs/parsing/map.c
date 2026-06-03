/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:14:05 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/03 18:35:38 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	flood_fill(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0); // Hors des limites, la map n'est pas fermée
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'X')
		return (1); // Mur ou déjà visité
	map->grid[y][x] = 'X'; //  visité
	// Vérifier les quatre directions
	return (flood_fill(map, x + 1, y) && flood_fill(map, x - 1, y) &&
			flood_fill(map, x, y + 1) && flood_fill(map, x, y - 1)); //renvoie 1 si tout renvoie 1
}

int	ft_forbidden(char c) //caracteres autorises ?
{
	if (c == '0' || c == '1' || c == ' ')
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1); 	//doublons ?
	return (2);
}

int	check_map(t_parsing *parsing, int fd)
{
	int player = 0;
	int isok = 0;
	while (gnl(fd)) //ligne par ligne
	{
		while (line[i]) //cara par cara
		{
			//check largeur de chaque ligne et garder max
			//incrementer longueur ++ dans game
			isok = ft_forbidden(***);
			if (isok == 1) //joueur
			{
				if (player)
					return (printerr("Multiple player\n"), 0);
				else
				{
					keep player position and orientation;
					player == 1;
				}
			}
			if (isok == 2)
				return (printerr("Forbidden character\n"), 0);
		}
		recup line dans lst //lst_add_back(&map_list, line);
		next_line;
	}
	if (!flood_fill(map, player_x, player_y))
		return (printerr("Map is not closed\n"), 0);
	return (1);
}

void fill_map(t_parsing *parsing, t_list *map_list)
{
	//convertir lst en grid
	//free lst
}
