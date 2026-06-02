/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/02 17:16:30 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_texture(t_map *map, char *line)
{
	if (!already_exist(line))
		return (printerr("Duplicate texture\n"), 0);
	if (access(line, R_OK) == -1)
		return (printerr("Cannot access texture\n"), 0);
	return (1);
}

int	check_color(t_map *map, char *line)
{
	if (!already_exist(line))
		return (printerr("Duplicate color\n"), 0);
	if (!good_color(line))
		return (printerr("Invalid color\n"), 0);
	return (1);
}

int read_file(char *path)
{
	int fd = open(path, O_RDONLY);
	int dup = 1;

	if (fd == -1)
	{
		printerr("Cannot open file\n");
		exit(1);
	}
	while (gnl(fd)) //ligne par ligne
	{
		if (line is empty)
			continue;
		else if (line starts with "NO " || "SO " || "WE " || "EA ")
			dup = check_texture(line);
		else if (ft_strcmp(line, "F ") == 0 || ft_strcmp(line, "C ") == 0)
			dup = check_color(line);
		if (dup == 0)
		{
			close(fd);
			exit(1);
		}
		else
			break;
	}
	check_map(map); //recuperer la map
}

void	check_args(int ac, char **av)
{
	int ext = 0;
	
	ext = ft_strlen(av[1]) - 4;
	if (ac != 2 || ft_strncmp(av[1] + ext, ".cub", 4) != 0 || access(av[1], R_OK) == -1)
	{
		printerr("Bad argument\n");
		exit(1);
	}
	read_file(av[1]);
}