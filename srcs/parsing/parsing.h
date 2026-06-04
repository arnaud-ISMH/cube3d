/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:01:21 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/04 13:20:00 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include "../../includes/cube3d.h"

typedef struct	s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct	s_parsing
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	t_map	map;
}	t_parsing;

typedef struct	s_list
{
	char			*line;
	struct s_list	*next;
}	t_list;

/*GRID*/
void	fill_map(t_parsing *parsing, t_list *map_list);
/*MAP*/
int		check_map(t_parsing *parsing, int fd);
int		ft_forbidden(char c);
int		flood_fill(t_map *map, int x, int y);
/*PARSING*/
int		check_color(t_parsing *parsing, char *line);
int		check_texture(t_parsing *parsing, char *line);
void	check_args(int ac, char **av);
int		read_file(char *arg);
int		is_identifier_free(char *line);
/*UTILS*/
void	printerr(char *msg);
int		max(int a, int b);
/*INIT*/
t_parsing	*init_parsing(void);

#endif