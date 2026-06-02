/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:14:05 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/02 18:02:54 by lchapot          ###   ########.fr       */
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
			flood_fill(map, x, y + 1) && flood_fill(map, x, y - 1));
}

int	ft_forbidden(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (2);
}

int	check_map(t_game *game) //take player pos
{
	int player = 0;
	int isok = 0;
	while (gnl(map)) //ligne par ligne
	{
		while (line[i]) //cara par cara
		{
			isok = ft_forbidden(***);
			if (isok == 1) //caractere de joueur
			{
				if (player)
					return (printerr("Multiple player\n"), 0);
				else
					player == 1;
			}
			if (isok == 2)
				return (printerr("Forbidden character\n"), 0);
			else 
				next_line + recup line dans lst
			i++;
		}
	}
	//caracteres non autorises ?
	//doublons ?
	//FLOODFILL verifier que la map est fermee, que le joueur peut acceder a tout les points de la map
	return (1);
}
