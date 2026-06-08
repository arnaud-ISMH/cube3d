/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:01:21 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/08 17:45:15 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "structs.h"

/*GRID*/
void		fill_map(t_parsing *parsing, t_list *map_list);
/*MAP*/
int			check_map(t_parsing *parsing, int fd, char *line);
int			ft_forbidden(char c);
int			flood_fill(t_map *map, int x, int y);
/*PARSING*/
int			check_color(t_parsing *parsing, char *line, char color);
int			check_texture(t_parsing *parsing, char *line, char texture);
void		check_args(int ac, char **av);
int			read_file(char *arg, t_parsing *parsing);
int			is_identifier_free(t_parsing *parsing, char *line);
/*UTILS*/
void		printerr(char *msg);
int			max(int a, int b);
/*INIT*/
t_parsing	*init_parsing(void);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*get_next_line(int fd);

/*A TEJ de utils*/
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
char		*ft_strdup(const char *s);
int			ft_lstsize(t_list *lst);

/*FREE*/
void	free_parsing(t_parsing *parsing);

#endif