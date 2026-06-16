/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:54:57 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/16 20:26:58 by lchapot          ###   ########.fr       */
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

static int	parse_header(int fd, t_parsing *parsing, char **line)
{
	char	**tok;
	int		res;

	while (*line)
	{
		if ((*line)[0] == '\n')
		{
			free(*line);
			*line = g_n_l(fd, 0);
			continue ;
		}
		tok = ft_split(*line, ' ');
		if (!tok || !tok[0])
			return (freefree(tok), free(*line), fp(parsing),
				printerr("Parse error\n"), 0);
		res = parse_line(parsing, tok);
		freefree(tok);
		if (res == -1)
			return (-1);
		if (res == 0)
			return (free(*line), fp(parsing), printerr("Bad element\n"), 0);
		free(*line);
		*line = g_n_l(fd, 0);
	}
	return (1);
}

int	read_file(char *arg, t_parsing *parsing)
{
	int		fd;
	int		res;
	char	*line;

	fd = open_fd(arg);
	if (!fd)
		return (0);
	line = g_n_l(fd, 0);
	if (!line)
		return (close(fd), printerr("Empty file\n"), 0);
	res = parse_header(fd, parsing, &line);
	if (res == 0)
		return (g_n_l(fd, 1), close(fd), 0);
	if (parsing->no == NULL || parsing->so == NULL || parsing->we == NULL
		|| parsing->ea == NULL || parsing->f == -1 || parsing->c == -1)
		return (g_n_l(fd, 1), close(fd), free(line),
			fp(parsing), printerr("Missing value\n"), 0);
	if (!check_map(parsing, fd, line))
		return (g_n_l(fd, 1), close(fd), fp(parsing), 0);
	return (g_n_l(fd, 1), close(fd), 1);
}
