/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:32:17 by adeflers          #+#    #+#             */
/*   Updated: 2026/01/31 23:32:17 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <stdbool.h>

typedef struct s_image
{
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}		t_image;

typedef struct s_keys
{
    bool w;
    bool a;
    bool s;
    bool d;
    bool left;
    bool right;
}   t_keys;

typedef struct s_player
{
	int		x;
	int		y;
	float	direction;
	int		move_speed;
	t_keys	keys;
}		t_player;

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
}		t_map;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_keys		keys;
	t_player	player;
	t_map		map;
}		t_mlx_data;

#endif
