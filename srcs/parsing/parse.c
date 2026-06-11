/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 15:22:09 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int is_identifier_free(t_parsing *parsing, char c)
{
	if (c == 'N')
		return (parsing->no == NULL);
	if (c == 'S')
		return (parsing->so == NULL);
	if (c == 'W')
		return (parsing->we == NULL);
	if (c == 'E')
		return (parsing->ea == NULL);
	if (c == '1')
		return (parsing->t1 == NULL);
	if (c == '2')
		return (parsing->t2 == NULL);
	if (c == 'F')
		return (parsing->f = -1);
	if (c == 'C')
		return (parsing->c = -1);
	return (0);
}

int	check_texture(t_parsing *parsing, char *line, char texture)
{
	int		ext;

	strip(line);
	ext = ft_strlen(line) - 4;
	if (ext < 0 && ft_strncmp(line + ext, ".xpm", 4) != 0)
		return (printerr("Invalid texture line\n"), 0); 
	if (!is_identifier_free(parsing, texture))
		return (printerr("Duplicate texture\n"), 0);
	if (access(line, R_OK) == -1)
		return (printerr("Cannot access texture\n"), 0);
	if (texture == 'N')
		parsing->no = ft_strdup(line);
	else if (texture == 'S')
		parsing->so = ft_strdup(line);
	else if (texture == 'W')
		parsing->we = ft_strdup(line);
	else if (texture == 'E')
		parsing->ea = ft_strdup(line); //ok?
	return (1);
}

int	good_color(char *line) //utils2
{
	if (!ft_isnumber(line) || (ft_atoi(line) < 0 || ft_atoi(line) > 255)) //ft_atoi !!!
		return (0);
	return (1);
}

int rgb_to_hex(int r, int g, int b) //utils2
{
	return (r << 16 | g << 8 | b);
}

int	check_color(t_parsing *parsing, char *line, char color) //atoi to ft_atoi!!!!
{
	char **colors;

	colors = ft_split(line, ',');
	//strip(colors[2]); //nn pcq atoi le fait deja
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
		return (printerr("Color issue\n"), 0);
	if (!is_identifier_free(parsing, color))
		return (freefree(colors), printerr("Duplicate color\n"), 0);
	if (!good_color(colors[0]) || !good_color(colors[1]) || !good_color(colors[2]))
		return (freefree(colors), printerr("Invalid color\n"), 0);
	if (color == 'F')
		parsing->f = rgb_to_hex(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	else if (color == 'C')
		parsing->c = rgb_to_hex(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	return (freefree(colors), 1);
}

static int	identify_line(char *id)
{
	if (ft_strncmp(id, "NO", 3) == 0 || ft_strncmp(id, "SO", 3) == 0
		|| ft_strncmp(id, "WE", 3) == 0 || ft_strncmp(id, "EA", 3) == 0)
		return (1);
	if (ft_strncmp(id, "F", 2) == 0 || ft_strncmp(id, "C", 2) == 0)
		return (2);
	if (ft_strncmp(id, "T1", 3) == 0 || ft_strncmp(id, "T2", 3) == 0)
		return (3);
	return (0);
}

static int	parse_line(t_parsing *parsing, char **tok)
{
	int	type;

	type = identify_line(tok[0]);
	if (type == 1)
		return (check_texture(parsing, tok[1], tok[0][0]));
	if (type == 2)
		return (check_color(parsing, tok[1], tok[0][0]));
	if (type == 3)
		return (texture_monster(parsing, tok[1], tok[0][1]));
	return (-1); // inconnu = début de map
}

int	read_file(char *arg, t_parsing *parsing)
{
	int		fd;
	int		res;
	char	*line;
	char	**tok;

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
		tok = ft_split(line, ' ');
		if (!tok || !tok[0]) //|| tok[2] ou osef?
			return (close(fd), freefree(tok), free(line), printerr("Parse error\n"), 0);
		res = parse_line(parsing, tok);
		freefree(tok);
		if (res == -1)
			break ;
		if (res == 0)
			return (close(fd), get_next_line(fd, 1), free(line), free_parsing(parsing), printerr("Error in element\n"), 0);
		free(line);
		line = get_next_line(fd, 0);
	}
	if (parsing->no == NULL || parsing->so == NULL || parsing->we == NULL
		|| parsing->ea == NULL || parsing->f == -1 || parsing->c == -1
		|| parsing->t1 == NULL || parsing->t2 == NULL)
		return (close(fd), free(line), printerr("Missing texture or color\n"), 0);
	if (!check_map(parsing, fd, line))
		return (close(fd), free_parsing(parsing), 0);
	return (close(fd), 1);
}