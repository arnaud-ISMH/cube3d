/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/04 17:11:33 by lchapot          ###   ########.fr       */
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
	char	**split;
	char	*path;
	split = ft_split(line, ' ');
	// if (!split || !split[0] || !split[1] || split[2])
	// {
	// 	free_split(split);
	// 	return (printerr("Invalid texture line\n"), 0);
	// }
	path = ft_strchr(split[1], '\n');
	if (path)
		*path = '\0';
	if (!is_identifier_free(parsing, line))
		return (printerr("Duplicate texture\n"), 0);
	if (access(split[1], R_OK) == -1)
		return (printerr("Cannot access texture\n"), 0);
	if (texture == 'N')
		parsing->no = split[1];
	else if (texture == 'S')
		parsing->so = split[1];
	else if (texture == 'W')
		parsing->we = split[1];
	else if (texture == 'E')
		parsing->ea = split[1];
	//check texture size doit etre carre? gnl max width max height
	return (1);
}

int	good_color(char *line)
{
	int a = 0;
	int b = 0;
	int c = 0;
	a = line[0] - '0'; //a remplacer par la partie a de la ligne
	// recup a b c
	if ((a < 0 || a > 255) || (b < 0 || b > 255) || (c < 0 || c > 255)) // pas rgb
		return (0);
	return (1);
}

int	check_color(t_parsing *parsing, char *line, char color)
{
	if (!is_identifier_free(parsing, line))
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

void read_file(char *arg, t_parsing *parsing)
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
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		printerr("Empty file\n");
		exit(1);
	}
	while (line)
	{
		if (line[0] == '\n')
			continue ;
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			dup = check_texture(parsing, line, line[0]);
		if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			dup = check_color(parsing, line, line[1]);
		if (dup == 0)
		{
			close(fd);
			free(line);
			printerr("Error in texture or color\n");
			// free init parsing ?
			exit(1);
		}
		else //debut map car ni vide ni content
			break;
		free(line);
		line = get_next_line(fd);
	}
	free(line); // ?
	if (parsing->no == NULL || parsing->so == NULL || parsing->we == NULL || parsing->ea == NULL || parsing->f == -1 || parsing->c == -1)
	{
		printf("%p, %p, %p, %p, %i, %i\n", parsing->no, parsing->so, parsing->we, parsing->ea, parsing->f, parsing->c);
		close(fd);
		printerr("Missing texture or color\n");
		exit(1);
	}
	check_map(parsing, fd); //recuperer la map
	close(fd);
}

void	check_args(int ac, char **av)
{
	int ext = 0;
	t_parsing *parsing;

	ext = ft_strlen(av[1]) - 4;
	if (ac != 2 || ft_strncmp(av[1] + ext, ".cub", 4) != 0 || access(av[1], R_OK) == -1)
	{
		printerr("Bad argument\n");
		exit(1);
	}
	parsing =init_parsing(); //init parsing et commencer a recup data
	read_file(av[1], parsing); //init parsing struct avant?
}


int main(int ac, char **av)
{
	check_args(ac, av);
	// printmap(parsing->map);
	//launch exec
	return (0);
}

