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

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>

# ifndef WIN_W
#  define WIN_W 1800
# endif
# ifndef WIN_H
#  define WIN_H 1000
# endif

typedef struct s_image
{
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}		t_image;

typedef struct s_point 
{
	float	x;
	int	x_flag;
	float	y;
	int	y_flag;
}		t_point;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_point		point;
	int			youhou_flag;
}		t_mlx_data;

int			close_win(t_mlx_data *data);
int			redraw(t_mlx_data *data);
t_mlx_data	minilibx_process(void);
int			handle_input(int keysym, t_mlx_data *data);
int			put_pixel(t_image *img, int x, int y, unsigned int color);

#endif
