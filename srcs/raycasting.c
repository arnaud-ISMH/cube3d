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
	int		scale;

	// Setup de la minimap 2D pour le dessin des rayons
	
	if (data->map.width > data->map.height)
		scale = (WIN_W / 4 / data->map.width);
	else
		scale = (WIN_H / 4 / data->map.height);

	rays = WIN_W; // 1 rayon par colonne de pixels sur la moitié droite
	
	i = 0;
	while (i < rays)
	{
		// camera_x va de -1 (bord gauche) à 1 (bord droit de l'écran 3D)
		double camera_x = 2.0 * i / (double)rays - 1.0;

		// Vecteur de direction du joueur (direction centrale)
		double dir_x = cos(data->player.direction);
		double dir_y = sin(data->player.direction);

		// Vecteur du plan de la caméra (perpendiculaire à la direction)
		// Le multiplicateur (ici 0.66) définit la largeur de ton FOV. 
		// 0.66 donne un FOV standard parfait de ~66 degrés.
		double plane_x = -dir_y * 0.66;
		double plane_y = dir_x * 0.66;

		// Direction exacte du rayon actuel (Vecteur combiné)
		float ray_dir_x = dir_x + plane_x * camera_x;
		float ray_dir_y = dir_y + plane_y * camera_x;
		// Position actuelle du rayon dans la grille (entiers)
		int map_x = (int)data->player.pos.x;
		int map_y = (int)data->player.pos.y;

		// Longueur du rayon d'une ligne de la grille à la suivante
		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);

		double side_dist_x;
		double side_dist_y;
		int step_x;
		int step_y;

		// Calcul des variables de départ du DDA
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player.pos.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player.pos.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player.pos.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player.pos.y) * delta_dist_y;
		}

		// --- LA BOUCLE DDA ---
		int hit = 0;
		int side = 0; // 0 pour vertical (Est/Ouest), 1 pour horizontal (Nord/Sud)
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			// Sécurité limites de la map
			if (map_x < 0 || map_x >= data->map.width || map_y < 0 || map_y >= data->map.height)
				break ;
			if (data->map.grid[map_y][map_x] == '1')
				hit = 1;
		}

		// --- CALCUL DE LA DISTANCE PERPENDICULAIRE (Anti Fish-eye automatique) ---
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		if (perp_wall_dist <= 0)
			perp_wall_dist = 0.01; // Évite la division par zéro si on colle un mur

		// --- DESSIN RENDU 3D ---
		// Hauteur de la ligne à dessiner à l'écran
		float wall_height = (int)(WIN_H / perp_wall_dist);

		// Calcul des pixels de départ et de fin
		int draw_start = (WIN_H / 2) - (wall_height / 2);
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = (WIN_H / 2) + (wall_height / 2);
		if (draw_end >= WIN_H)
			draw_end = WIN_H - 1;

		/* unsigned int color; */
		/* if (side == 0) */
		/* { */
		/* 	if (ray_dir_x > 0) */
		/* 		color = 0xFFFF00; // Mur Est */
		/* 	else */
		/* 		color = 0xFF00FF; // Mur Ouest */
		/* } */
		/* else */
		/* { */
		/* 	if (ray_dir_y > 0) */
		/* 		color = 0x00FFFF; // Mur Sud */
		/* 	else */
		/* 		color = 0x0000FF; // Mur Nord */
		/* } */
		/**/
		/* // On trace la colonne de mur à l'écran sans toucher la minimap (1/4 de l'écran) */
		/* int screen_x = i; */
		/* int y_pixel = draw_start; */
		/* while (y_pixel < draw_end) */
		/* { */
		/* 	if (screen_x <= WIN_W / 4 && y_pixel <= WIN_H / 4) */
		/* 	{ */
		/* 		y_pixel++; */
		/* 		continue ; */
		/* 	} */
		/* 	put_pixel(&data->img, screen_x, y_pixel, color); */
		/* 	y_pixel++; */
		/* } */

		// --- 1. SÉLECTION DE LA TEXTURE SELON L'ORIENTATION ---
        t_texture *tex;
        double wall_x; // Position exacte de l'impact sur le mur (0.0 à 1.0)

        if (side == 0)
        {
            if (ray_dir_x > 0)
                tex = &data->texture_west; // Impact sur la face OUEST (le rayon va vers l'Est)
            else
                tex = &data->texture_east; // Impact sur la face EST (le rayon va vers l'Ouest)
            wall_x = data->player.pos.y + perp_wall_dist * ray_dir_y;
        }
        else
        {
            if (ray_dir_y > 0)
                tex = &data->texture_north; // Impact sur la face NORD (le rayon va vers le Sud)
            else
                tex = &data->texture_south; // Impact sur la face SUD (le rayon va vers le Nord)
            wall_x = data->player.pos.x + perp_wall_dist * ray_dir_x;
        }
        wall_x -= floor(wall_x); // On ne garde que la partie décimale

        // --- 2. CALCUL DE TEX_X (La colonne correspondante de la texture) ---
        int tex_x = (int)(wall_x * (double)tex->width);

        // Correction de l'effet miroir de la texture sur certaines faces
        if (side == 0 && ray_dir_x > 0)
            tex_x = tex->width - tex_x - 1;
        if (side == 1 && ray_dir_y < 0)
            tex_x = tex->width - tex_x - 1;

        // --- 3. PRÉPARATION DE L'INTERPOLATION VERTICALE ---
        // tex_step indique de combien de pixels de texture on avance pour 1 pixel écran
        double tex_step = 1.0 * tex->height / wall_height;
        
        // Position de départ dans la texture (gère les cas où le mur dépasse en haut de l'écran)
        double tex_pos = (draw_start - WIN_H / 2 + wall_height / 2) * tex_step;

        // --- 4. TRACÉ DE LA COLONNE VERTICALE AVEC TEXTURE ---
        int screen_x = i;
        int y_pixel = draw_start;
        while (y_pixel < draw_end)
        {
            // Calcul du tex_y actuel (on protège contre les débordements de taille)
            int tex_y = (int)tex_pos % tex->height;
            if (tex_y < 0)
                tex_y = 0;
            tex_pos += tex_step;

            // Sécurité pour ne pas dessiner par-dessus ta minimap au quart supérieur gauche
            if (screen_x <= WIN_W / 4 && y_pixel <= WIN_H / 4)
            {
                y_pixel++;
                continue ;
            }

            // Calcul de l'offset mémoire pour piocher le pixel de la texture chargée
            int tex_offset = (tex_y * tex->size_line) + (tex_x * (tex->bpp / 8));
            unsigned int color = *(unsigned int *)(tex->img_data + tex_offset);

            /* // OPTIONNEL : Ombrage pour donner du relief 3D */
            /* // On assombrit légèrement les faces Est/Ouest en divisant les couleurs par 2 (Bitwise shift) */
            /* if (side == 0) */
            /*     color = (color >> 1) & 0x7F7F7F; */

            // On pousse le pixel de texture sur ton image d'écran principale
            put_pixel(&data->img, screen_x, y_pixel, color);
            y_pixel++;
        }

		// On trace une ligne de points entre le joueur et le mur sur la minimap

		double ray_length_2d = (side == 0) ? (side_dist_x - delta_dist_x) : (side_dist_y - delta_dist_y);
		int k = 0;
		while (k < (int)(ray_length_2d * scale))
		{
			int r_x = (int)(data->player.pos.x * scale) + (int)(ray_dir_x * k);
			int r_y = (int)(data->player.pos.y * scale) + (int)(ray_dir_y * k);
			put_pixel(&data->img, r_x, r_y, 0x555555); // Rayons gris discrets sur la map
			k++;
		}
		i++;
	}
}
