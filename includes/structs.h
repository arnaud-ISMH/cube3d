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

/********************* Fun ******************************/

typedef struct s_point
{
	float	x;
	int		x_flag;
	float	y;
	int		y_flag;
}		t_point;

typedef struct s_object
{
	t_point			origin;
	float			speed;
	int				youhou_flag;
	int				large;
	int				haut;
	unsigned int	color;
}		t_object;

/********************* Fun ******************************/

typedef struct s_image
{
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}		t_image;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_object	square; // fun
	t_object	bordures;
	int			count_frame;
}		t_mlx_data;

#endif
