/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:56:51 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/03 17:56:51 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	raycasting(t_mlx_data *data)
{
	int		rays;
	int		i;
	float	fov;
	float	start;
	float	step;

	rays = 1000;
	fov = M_PI / 2;
	start = data->player.direction - fov / 2;
	step = fov / rays;
	i = 0;
	while (i < rays)
	{
		float angle = start + i * step;
		float dx = cos(angle);
		float dy = sin(angle);
		float x = data->player.pos.x;
		float y = data->player.pos.y;

		int j = 0;
		while (j < WIN_W)
		{
			x+=dx;
			y+=dy;
			if (is_wall(data, (int)x, (int)y))
				break ;
			j++;
			put_pixel(&data->img, data->player.pos.x + (int)(dx * j), data->player.pos.y + (int)(dy * j), 0xAAAAFF);
			/* put_pixel(&data->img, (int)(WIN_W/ 2 + i * (WIN_W / rays)), (int)(WIN_H / 2 + j), 0xAAAAFF); */
		}
		// On calcule l'angle relatif du rayon par rapport à la direction du joueur
		float relative_angle = angle - data->player.direction;

		// On corrige la distance (j) pour éliminer l'effet Fish-eye
		j = j * cos(relative_angle);
		if (j > 0) // Sécurité anti-division par 0
        {
            // 2. Calcul de la hauteur inversement proportionnelle
            // (Tu peux changer le multiplicateur 25000 pour étirer/aplatir tes murs)
            int wall_height = (int)((WIN_H * 40) / j); 
            
            // 3. Calcul du centrage vertical
            int draw_start = (WIN_H / 2) - (wall_height / 2);
            if (draw_start < 0)
                draw_start = 0;
            int draw_end = (WIN_H / 2) + (wall_height / 2);
            if (draw_end >= WIN_H)
                draw_end = WIN_H - 1;

            // 4. Calcul de la position X sur la moitié DROITE de l'écran
            int screen_x = (WIN_W / 2) + i;

            // 5. On trace la ligne verticale du mur en 3D
            int y_pixel = draw_start;
            while (y_pixel < draw_end)
            {
                put_pixel(&data->img, screen_x, y_pixel, 0x0000FF); // Mur bleu
                y_pixel++;
            }
        }
		i++;
	}
}
