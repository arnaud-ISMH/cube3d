/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:35:11 by adeflers          #+#    #+#             */
/*   Updated: 2026/01/29 10:03:48 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "fun.h"
# include "structs.h"
# include <math.h>

# ifndef WIN_W
#  define WIN_W 1800.0
# endif
# ifndef WIN_H
#  define WIN_H 1000.0
# endif

int			close_win(t_mlx_data *data);
int			redraw(t_mlx_data *data);
t_mlx_data	minilibx_process(void);
int			handle_input(int keysym, t_mlx_data *data);
int			put_pixel(t_image *img, int x, int y, unsigned int color);

#endif
