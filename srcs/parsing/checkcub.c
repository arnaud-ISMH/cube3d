/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:34:14 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 16:48:49 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_map(t_parsing *parsing, int fd, char *line)
{
	t_list	*map_lst;

	map_lst = NULL;
	while (line)
	{
		parsing->map.width = max(parsing->map.width, (ft_strlen(line) - 1));
		parsing->map.height++;
		ft_lstadd_back(&map_lst, ft_lstnew(line));
		line = get_next_line(fd, 0);
	}
	fill_map(parsing, map_lst);
	ft_lstclear(&map_lst, free);
	if (!parse_map(parsing))
		return (get_next_line(fd, 1), printerr("Map error\n"), 0);
	if (!flood_fill(&parsing->map, parsing->player_x, parsing->player_y))
		return (get_next_line(fd, 1), printerr("Map is not closed\n"), 0);
	return (1);
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
		parsing->ea = ft_strdup(line);
	return (1);
}

int	check_color(t_parsing *parsing, char *line, char color)
{
	char	**col;

	col = ft_split(line, ',');
	if (!col || !col[0] || !col[1] || !col[2] || col[3])
		return (printerr("Color issue\n"), 0);
	if (!is_identifier_free(parsing, color))
		return (freefree(col), printerr("Duplicate color\n"), 0);
	if (!good_color(col[0]) || !good_color(col[1]) || !good_color(col[2]))
		return (freefree(col), printerr("Invalid color\n"), 0);
	if (color == 'F')
		parsing->f = rgb2hex(ft_atoi(col[0]), ft_atoi(col[1]), ft_atoi(col[2]));
	else if (color == 'C')
		parsing->c = rgb2hex(ft_atoi(col[0]), ft_atoi(col[1]), ft_atoi(col[2]));
	return (freefree(col), 1);
}
