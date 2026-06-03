/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:01:21 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/02 18:12:56 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# Usernameinclude "../../includes/cube3d.h"

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	char    **grid;
    int     width;
    int     height;
}   t_map;

// typedef struct s_parsing
// {
//     t_map   map;
//     char    **map_data;
// }   t_parsing;



#endif