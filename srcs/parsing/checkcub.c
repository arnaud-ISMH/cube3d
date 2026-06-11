/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:34:14 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 15:36:37 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_map(t_parsing *parsing, int fd, char *line)
{
	t_list *map_lst = NULL;

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
		parsing->ea = ft_strdup(line); //ok?
	return (1);
}

int	check_color(t_parsing *parsing, char *line, char color) //atoi to ft_atoi!!!!
{
	char **colors;

	colors = ft_split(line, ',');
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