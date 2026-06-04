/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/04 14:15:07 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_identifier_free(t_parsing *parsing, char *line)
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

int	check_texture(t_parsing *parsing, char *line, char texture)
{
	if (!is_identifier_free(&parsing,line))
		return (printerr("Duplicate texture\n"), 0);
	if (access(line, R_OK) == -1)
		return (printerr("Cannot access texture\n"), 0);
	//parse texture, one or more spaces
	if (texture == 'N')
		parsing->no = line; //a remplacer par le path
	else if (texture == 'S')
		parsing->so = line;
	else if (texture == 'W')
		parsing->we = line;
	else if (texture == 'E')
		parsing->ea = line;
	//check texture size doit etre carre? gnl max width max height
	return (1);
}

int	good_color(char *line)
{
	int a = 0;
	int b = 0;
	int c = 0;
	// recup a b c
	if ((a < 0 || a > 255) || (b < 0 || b > 255) || (c < 0 || c > 255)) // pas rgb
		return (0);
	return (1);
}
int	check_color(t_parsing *parsing, char *line, char color)
{
	if (!is_identifier_free(&parsing, line))
		return (printerr("Duplicate color\n"), 0);
	if (!good_color(line))
		return (printerr("Invalid color\n"), 0);
	//parse color
	if (color == 'F')
		parsing->f = 1; //a remplacer par la couleur
	else if (color == 'C')
		parsing->c = 1; //a remplacer par la couleur
	return (1);
}

int read_file(char *arg)
{
	int fd = open(arg, O_RDONLY);
	int dup = 1;
	char *line;
	if (fd == -1)
	{
		printerr("Cannot open file\n");
		//free init parsing?
		exit(1);
	}
	while (line = get_next_line(fd)) //ligne par ligne
	{
		if (!line)
			continue ;
		else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			dup = check_texture(&parsing, line, line[0]);
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			dup = check_color(&parsing, line, line[1]);
		if (dup == 0)
		{
			close(fd);
			// free init parsing
			exit(1);
		}
		else //debut map car ni vide ni content
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
	// init_parsing(); //init parsing et commencer a recup data
	read_file(av[1]); //init parsing struct avant?
}


int main(int ac, char **av)
{
	check_args(ac, av);
	// printmap(parsing->map);
	//launch exec
	return (0);
}
