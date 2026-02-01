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

# ifndef SIZE
#  define SIZE 100
# endif

# ifndef SPEED
#  define SPEED 15
# endif


void	init_square(t_mlx_data *data);
void	clamping(t_mlx_data *data);
int		draw_pixel_group(t_mlx_data *data);
void	youhou(t_mlx_data *data);
void	handle_input_fun(int keysym, t_mlx_data *data);

#endif
