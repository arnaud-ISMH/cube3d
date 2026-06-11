/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 12:57:55 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

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
	if (texture == 'N')
		parsing->no = ft_strdup(split[1]);
	else if (texture == 'S')
		parsing->so = ft_strdup(split[1]);
	else if (texture == 'W')
		parsing->we = ft_strdup(split[1]);
	else if (texture == 'E')
		parsing->ea = ft_strdup(split[1]); //ok?
	return (freefree(split), 1);
}

int ft_isnumber(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] < 48 || line[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	good_color(char *line)
{
	if (!ft_isnumber(line) || (atoi(line) < 0 || atoi(line) > 255)) //ft_atoi !!!
		return (0);
	return (1);
}

int	check_color(t_parsing *parsing, char *line, char color) //atoi to ft_atoi!!!!
{
	char **split;
	char **colors;

	split = ft_split(line, ' ');
	if (!split)
		return (printerr("Color issue\n"), 0);
	colors = ft_split(split[1], ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
		return (freefree(split), printerr("Color issue\n"), 0);
	if (!is_identifier_free(parsing, line))
		return (freefree(split), freefree(colors), printerr("Duplicate color\n"), 0);
	if (!good_color(colors[0]) || !good_color(colors[1]) || !good_color(colors[2]))
		return (freefree(split), freefree(colors), printerr("Invalid color\n"), 0);
	if (color == 'F')
		parsing->f = (t_color){atoi(colors[0]), atoi(colors[1]), atoi(colors[2])};
	else if (color == 'C')
		parsing->c = (t_color){atoi(colors[0]), atoi(colors[1]), atoi(colors[2])};
	return (freefree(split), freefree(colors), 1);
}

int	open_fd(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		printerr("Cannot open file\n");
		// free_parsing(parsing); //pr linstant pas besoin mais secu
		exit(1);		
	}
	return (fd);
}

int	read_file(char *arg, t_parsing *parsing)
{
	int fd;
	int dup = 1;
	char *line;

	fd = open_fd(arg);
	line = get_next_line(fd, 0);
	if (!line)
		return (close(fd), printerr("Empty file\n"), 0);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd, 0);
			continue ;
		}
		else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			dup = check_texture(parsing, line, line[0]);
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			dup = check_color(parsing, line, line[0]);
		else
			break;
		if (dup == 0)
			return (close(fd), get_next_line(fd, 1), free(line), free_parsing(parsing), printerr("Error in texture or color\n"), 0);
		free(line);
		line = get_next_line(fd, 0);
	}
	// printf("%p, %p, %p, %p, %i, %i\n", parsing->no, parsing->so, parsing->we, parsing->ea, parsing->f.r, parsing->c.r);
	if (parsing->no == NULL || parsing->so == NULL || parsing->we == NULL || parsing->ea == NULL || parsing->f.r == -1 || parsing->c.r == -1)
		return (close(fd), free(line), printerr("Missing texture or color\n"), 0);
	if (!check_map(parsing, fd, line))
		return(close(fd), free_parsing(parsing), 0); //free(line) deja fait dans check map normalement
	return (close(fd), 1);
}

t_parsing *check_args(int ac, char **av)
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
	return (parsing);
}
