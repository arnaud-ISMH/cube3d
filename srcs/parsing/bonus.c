/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:22:40 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 13:15:42 by lchapot          ###   ########.fr       */
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

int check_door(t_parsing *parsing, int x, int y)
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
	char	**split;
	int		ext;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
		return (printerr("Invalid texture line\n"), 0);
	strip(split[1]);
	ext = ft_strlen(split[1]) - 4;
	if (ext < 0 && ft_strncmp(split[1] + ext, ".xpm", 4) != 0)
		return (freefree(split), printerr("Invalid texture line\n"), 0); 
	if (!is_identifier_free(parsing, line))
		return (freefree(split), printerr("Duplicate texture\n"), 0);
	if (access(split[1], R_OK) == -1)
		return (freefree(split), printerr("Cannot access texture\n"), 0);
	if (texture == '1')
		parsing->no = ft_strdup(split[1]);
	else if (texture == '2')
		parsing->so = ft_strdup(split[1]);
	return (freefree(split), 1);
}