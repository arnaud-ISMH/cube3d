/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:22:40 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 16:36:15 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	count_entities(t_parsing *parsing, int *ndoors, int *nmonsters)
{
	int	i;
	int	j;

	i = 0;
	while (parsing->map.grid[i])
	{
		j = 0;
		while (parsing->map.grid[i][j])
		{
			if (parsing->map.grid[i][j] == 'D')
				(*ndoors)++;
			if (parsing->map.grid[i][j] == 'X')
				(*nmonsters)++;
			j++;
		}
		i++;
	}
}

int	check_door(t_parsing *parsing, int x, int y)
{
	t_map	*m;

	m = &parsing->map;
	if (x == 0 || y == 0 || x == m->width - 1 || y == m->height - 1)
		return (printerr("Door on border\n"), 0);
	if ((m->grid[y][x - 1] == '1' && m->grid[y][x + 1] == '1')
		|| (m->grid[y - 1][x] == '1' && m->grid[y + 1][x] == '1'))
	{
		parsing->door[parsing->door_count++] = (t_door){x, y, 0};
		return (1);
	}
	return (printerr("Invalid door placement\n"), 0);
}

int	texture_monster(t_parsing *parsing, char *line, char texture)
{
	int		ext;

	strip(line);
	ext = ft_strlen(line) - 4;
	if (ext < 0 || ft_strncmp(line + ext, ".xpm", 4) != 0)
		return (printerr("Invalid texture line\n"), 0);
	if (!is_identifier_free(parsing, texture))
		return (printerr("Duplicate texture\n"), 0);
	if (access(line, R_OK) == -1)
		return (printerr("Cannot access texture\n"), 0);
	if (texture == '1')
		parsing->t1 = ft_strdup(line);
	else if (texture == '2')
		parsing->t2 = ft_strdup(line);
	return (1);
}
