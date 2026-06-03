/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:01:21 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/03 17:26:50 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# Usernameinclude "../../includes/cube3d.h"

typedef struct s_map
{

	char    **grid;
    int     width;
    int     height;
}   t_map;

typedef struct s_parsing
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
    t_map   map;
}   t_parsing;



#endif