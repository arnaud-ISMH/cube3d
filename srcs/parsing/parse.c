/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 13:57:31 by lchapot          ###   ########.fr       */
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
	if (ft_strncmp(line, "T1 ", 3) == 0)
		return (parsing->t1 == NULL);
	if (ft_strncmp(line, "T2 ", 3) == 0)
		return (parsing->t2 == NULL);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parsing->f = -1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parsing->c = -1);
	return (0);
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

int	good_color(char *line)
{
	if (!ft_isnumber(line) || (ft_atoi(line) < 0 || ft_atoi(line) > 255)) //ft_atoi !!!
		return (0);
	return (1);
}

int rgb_to_hex(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int	check_color(t_parsing *parsing, char *line, char color) //atoi to ft_atoi!!!!
{
	char **split;
	char **colors;

	split = ft_split(line, ' ');
	if (!split)
		return (printerr("Color issue\n"), 0);
	colors = ft_split(split[1], ',');
	//strip(colors[2]);
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
		return (freefree(split), printerr("Color issue\n"), 0);
	if (!is_identifier_free(parsing, line))
		return (freefree(split), freefree(colors), printerr("Duplicate color\n"), 0);
	if (!good_color(colors[0]) || !good_color(colors[1]) || !good_color(colors[2]))
		return (freefree(split), freefree(colors), printerr("Invalid color\n"), 0);
	if (color == 'F')
		parsing->f = rgb_to_hex(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	else if (color == 'C')
		parsing->c = rgb_to_hex(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	return (freefree(split), freefree(colors), 1);
}


int	read_file(char *arg, t_parsing *parsing) //marche pas si "    SO    " ??
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
		else if (ft_strncmp(line, "T1 ", 3) == 0 || ft_strncmp(line, "T2 ", 3) == 0)
			dup = texture_monster(parsing, line, line[1]);
		else
			break;
		if (dup == 0)
			return (close(fd), get_next_line(fd, 1), free(line), free_parsing(parsing), printerr("Error in texture or color\n"), 0);
		free(line);
		line = get_next_line(fd, 0);
	}
	// printf("%p, %p, %p, %p, colors %i, %i, t1 %p t2 %p\n", parsing->no, parsing->so, parsing->we, parsing->ea, parsing->f, parsing->c, parsing->t1, parsing->t2);
	if (parsing->no == NULL || parsing->so == NULL || parsing->we == NULL || 
		parsing->ea == NULL || parsing->f == -1 || parsing->c == -1 || parsing->t1 == NULL || parsing->t2 == NULL)
		return (close(fd), free(line), printerr("Missing texture or color\n"), 0);
	if (!check_map(parsing, fd, line))
		return(close(fd), free_parsing(parsing), 0); //free(line) deja fait dans check map normalement
	return (close(fd), 1);
}
