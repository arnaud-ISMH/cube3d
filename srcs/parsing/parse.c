/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/04 13:34:30 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_identifier_free(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parsing->no == NULL);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (parsing->so == NULL);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (parsing->we == NULL);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (parsing->ea == NULL);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parsing->f == -1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parsing->c == -1);
	return (0);
}

int	check_texture(t_parsing *parsing, char *line)
{
	if (!is_identifier_free(line))
		return (printerr("Duplicate texture\n"), 0);
	if (access(line, R_OK) == -1)
		return (printerr("Cannot access texture\n"), 0);
	//check texture size doit etre carre?
	return (1);
}

int	check_color(t_parsing *parsing, char *line)
{
	if (!is_identifier_free(line))
		return (printerr("Duplicate color\n"), 0);
	if (!good_color(line))
		return (printerr("Invalid color\n"), 0);
	return (1);
}

int read_file(char *arg)
{
	int fd = open(arg, O_RDONLY);
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
			dup = check_texture(&parsing, line);
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
	check_map(&parsing, fd); //recuperer la map
	close(fd);
	return (1);
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
	read_file(av[1]); //init parsing struct avant?
}