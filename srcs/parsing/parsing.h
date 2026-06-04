/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:01:21 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/04 18:06:52 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include "../../includes/cube3d.h"
# include <stdlib.h>
# include <stdio.h>
typedef struct	s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct	s_color
{
	int r;
	int g;
	int b;
}	t_color;

typedef struct	s_parsing
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	f;
	t_color	c;
	int player_x;
	int player_y;
	char player_orientation;
	t_map	map;
}	t_parsing;

// typedef struct	s_list
// {
// 	char			*line;
// 	struct s_list	*next;
// }	t_list;

/*GRID*/
void		fill_map(t_parsing *parsing, t_list *map_list);
/*MAP*/
int			check_map(t_parsing *parsing, int fd, char *line);
int			ft_forbidden(char c);
int			flood_fill(t_parsing *parsing);
/*PARSING*/
int			check_color(t_parsing *parsing, char *line, char color);
int			check_texture(t_parsing *parsing, char *line, char texture);
void		check_args(int ac, char **av);
void		read_file(char *arg, t_parsing *parsing);
int			is_identifier_free(t_parsing *parsing, char *line);
/*UTILS*/
void		printerr(char *msg);
int			max(int a, int b);
/*INIT*/
t_parsing	*init_parsing(void);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*get_next_line(int fd);

#endif