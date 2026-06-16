/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/16 17:19:20 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_identifier_free(t_parsing *parsing, char c)
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
		return (parsing->f == -1);
	if (c == 'C')
		return (parsing->c == -1);
	return (0);
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
	return (-1);
}

int	read_file(char *arg, t_parsing *parsing)
{
	int		fd;
	int		res;
	char	*line;
	char	**tok;

	fd = open_fd(arg);
	if (!fd)
		return (0);
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
			return (close(fd), freefree(tok), free(line), free_parsing(parsing), ("Parse error\n"), 0);
		res = parse_line(parsing, tok);
		freefree(tok);
		if (res == -1)
			break ;
		if (res == 0)
			return (get_next_line(fd, 1), close(fd), free(line), free_parsing(parsing), printerr("Error in element\n"), 0);
		free(line);
		line = get_next_line(fd, 0);
	}
	if (parsing->no == NULL || parsing->so == NULL || parsing->we == NULL
		|| parsing->ea == NULL || parsing->f == -1 || parsing->c == -1)
		return (get_next_line(fd, 1), close(fd), free(line), free_parsing(parsing), printerr("Missing texture or color\n"), 0);
	if (!check_map(parsing, fd, line))
		return (get_next_line(fd, 1), close(fd), free_parsing(parsing), 0);
	return (get_next_line(fd, 1), close(fd), 1);
}
//parsing->f == -1 || parsing->c == -1