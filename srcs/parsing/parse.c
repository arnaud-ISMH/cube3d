/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/07 16:42:10 by lchapot          ###   ########.fr       */
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
		return (parsing->f.r == -1 && parsing->f.g == -1 && parsing->f.b == -1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parsing->c.r == -1 && parsing->c.g == -1 && parsing->c.b == -1);
	return (0);
}

void	strip(char *s)
{
	char *res;

	res = ft_strchr(s, '\n');
	if (res)
		*res = '\0';
}

int	check_texture(t_parsing *parsing, char *line, char texture)
{
	char	**split;
	int		ext;

	split = ft_split(line, ' ');
	// if (!split || !split[0] || !split[1] || split[2])
	// 	return (printerr("Invalid texture line\n"), freesplit(split), 0);
	strip(split[1])//si trouve pas de \n?
	ext = ft_strlen(split[1]) - 4;
	if (ext < 0 && ft_strncmp(split[1] + ext, ".xpm", 4) != 0)
		return (printerr("Invalid texture line\n"), 0); //free split
	if (!is_identifier_free(parsing, line))
		return (printerr("Duplicate texture\n"), 0); //freesplit
	if (access(split[1], R_OK) == -1)
		return (printerr("Cannot access texture\n"), 0); //freesplit
	if (texture == 'N')
		parsing->no = split[1];
	else if (texture == 'S')
		parsing->so = split[1];
	else if (texture == 'W')
		parsing->we = split[1];
	else if (texture == 'E')
		parsing->ea = split[1];
	return (free(split[0]), free(split), 1); //freesplit[1] en fin;
}

int	good_color(char *line)
{
	int a = 0;

	a = atoi(line); //ft_atoi retourne 0 si pas number? donc verifier dabord si number?
	if ((a < 0 || a > 255)) // pas rgb
		return (0);
	return (1);
}

int	check_color(t_parsing *parsing, char *line, char color)
{
	char **split;
	split = ft_split(line, ' '); //if ! split et free etc bref
	char **colors = ft_split(split[1], ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
		return (printerr("Color issue\n"), 0); //free split;
	if (!is_identifier_free(parsing, line))
		return (printerr("Duplicate color\n"), 0); //freepslit
	if (!good_color(colors[0]) || !good_color(colors[1]) || !good_color(colors[2]))
		return (printerr("Invalid color\n"), 0); //freesplit
	if (color == 'F')
		parsing->f = (t_color){atoi(colors[0]), atoi(colors[1]), atoi(colors[2])}; //ft_atoi
	else if (color == 'C')
		parsing->c = (t_color){atoi(colors[0]), atoi(colors[1]), atoi(colors[2])};
	return (1); //freesplit
}

int	open_fd(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		printerr("Cannot open file\n");
		//free init parsing?
		exit(1);		
	}
	return (fd);
}

intread_file(char *arg, t_parsing *parsing)
{
	int fd;
	int dup = 1;
	char *line;

	fd = open_fd(arg);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), printerr("Empty file\n"), 0);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			dup = check_texture(parsing, line, line[0]);
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			dup = check_color(parsing, line, line[0]);
		else
			break;
		if (dup == 0)
			return (close(fd), free(line), printerr("Error in texture or color\n"), 0);// free init parsing ?
		free(line);
		line = get_next_line(fd);
	}
	printf("%p, %p, %p, %p, %i, %i\n", parsing->no, parsing->so, parsing->we, parsing->ea, parsing->f.r, parsing->c.r);
	if (parsing->no == NULL || parsing->so == NULL || parsing->we == NULL || parsing->ea == NULL || parsing->f.r == -1 || parsing->c.r == -1)
		return (close(fd), printerr("Missing texture or color\n"), 0);
	if (!check_map(parsing, fd, line))
		return(close(fd), 0); //recuperer la map
	return (close(fd), 1);
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
	parsing = init_parsing();
	if (!read_file(av[1], parsing))
		exit(1);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	check_args(ac, av);
	//launch exec
	return (1);
}

