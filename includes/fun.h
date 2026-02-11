/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:30:16 by adeflers          #+#    #+#             */
/*   Updated: 2026/01/31 23:30:16 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUN_H
# define FUN_H

# include "structs.h"

# ifndef COLOR
#  define COLOR 0xFFFFFF
# endif

# ifndef ROUGE
# define ROUGE 0xFF0000
# endif

#ifndef VERT
# define VERT 0x00FF00
# endif

#ifndef BLEU
# define BLEU 0x0000FF
# endif

# ifndef JAUNE
#  define JAUNE 0xFFFF00
# endif

# ifndef ORANGE
#  define ORANGE 0xFFA500
# endif

#ifndef PINK
# define PINK 0xFFC0CB
# endif

# ifndef SIZE
#  define SIZE 20
# endif

# ifndef SPEED
#  define SPEED 10
# endif

# ifndef BORDURE_SIZE
#  define BORDURE_SIZE 50
# endif

void	init_square(t_mlx_data *data);
void	init_board(t_mlx_data *data);
void	clamping(t_mlx_data *data);
int		draw_pixel_group(t_mlx_data *data);
void	youhou(t_mlx_data *data);
void	handle_input_fun(int keysym, t_mlx_data *data);
void	raycasting(t_mlx_data *data);

#endif
