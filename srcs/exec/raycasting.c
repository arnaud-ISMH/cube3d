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

#include "../../includes/cube3d.h"

void	get_ray_vect(t_mlx_data *data, t_raycast *ray, int i)
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	camera_x = 2.0 * i / (double)WIN_W - 1.0; // camera_x va de -1 (bord gauche) à 1 (bord droit de l'écran 3D)
	// Vecteur de direction du joueur (direction centrale)
	dir_x = cos(data->player.direction);
	dir_y = sin(data->player.direction);
	// Vecteur du plan de la caméra (perpendiculaire à la direction)
	// 0.66 donne un FOV standard de ~66 degrés.
	plane_x = -dir_y * 0.66;
	plane_y = dir_x * 0.66;
	// Direction exacte du rayon actuel (Vecteur combiné)
	ray->ray_dir_x = dir_x + plane_x * camera_x;
	ray->ray_dir_y = dir_y + plane_y * camera_x;

	// Position actuelle du rayon dans la grille (entiers)
	ray->map_x = (int)data->player.pos.x;
	ray->map_y = (int)data->player.pos.y;
	// Longueur du rayon d'une ligne de la grille à la suivante
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30; // Un grand nombre pour éviter la division par zéro
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30; // Un grand nombre pour éviter la division par zéro
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void	draw_rays_minimap(t_mlx_data *data, t_raycast ray)
{
	double ray_length_2d;
	int k;
	int r_x;
	int r_y;

	if (ray.side == 0)
		ray_length_2d = (ray.side_dist_x - ray.delta_dist_x);
	else
		ray_length_2d = (ray.side_dist_y - ray.delta_dist_y);
	k = 0;
	while (k < (int)(ray_length_2d * data->map.scale))
	{
		r_x = (int)(data->player.pos.x * data->map.scale) + (int)(ray.ray_dir_x * k);
		r_y = (int)(data->player.pos.y * data->map.scale) + (int)(ray.ray_dir_y * k);
		put_pixel(&data->img, r_x, r_y, 0x555555);
		k++;
	}
}

void	init_dda(t_mlx_data *data, t_raycast *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos.x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos.y) * ray->delta_dist_y;
	}
}

void	dda_loop(t_mlx_data *data, t_raycast *ray)
{
	ray->side = 0; // 0 pour vertical (Est/Ouest), 1 pour horizontal (Nord/Sud)
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		// Sécurité limites de la map
		if (ray->map_x < 0 || ray->map_x >= data->map.width || ray->map_y < 0 || ray->map_y >= data->map.height)
			break ;
		if (data->map.grid[ray->map_y][ray->map_x] == '1')
			break ;
	}
}

void	fish_eye_correction(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);

	if (ray->perp_wall_dist <= 0)
		ray->perp_wall_dist = 0.01; // Évite la division par zéro si on colle un mur


}

void	choose_tex(t_mlx_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex = &data->texture_west; // Impact sur la face OUEST (le rayon va vers l'Est)
		else
			ray->tex = &data->texture_east; // Impact sur la face EST (le rayon va vers l'Ouest)
		ray->wall_x = data->player.pos.y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->tex = &data->texture_north; // Impact sur la face NORD (le rayon va vers le Sud)
		else
			ray->tex = &data->texture_south; // Impact sur la face SUD (le rayon va vers le Nord)
		ray->wall_x = data->player.pos.x + ray->perp_wall_dist * ray->ray_dir_x;
	}
}

void	draw_tex_on_wall(t_mlx_data *data, t_raycast *ray, int i)
{
	ray->screen_x = i;
	ray->y_pixel = ray->draw_start;
	while (ray->y_pixel < ray->draw_end)
	{
		// Calcul du tex_y actuel (on protège contre les débordements de taille)
		ray->tex_y = (int)ray->tex_pos % ray->tex->height;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		ray->tex_pos += ray->tex_step;

		// Sécurité pour ne pas dessiner par-dessus la minimap au quart supérieur gauche
		if (ray->screen_x <= WIN_W / 4 && ray->y_pixel <= WIN_H / 4)
		{
			ray->y_pixel++;
			continue ;
		}

		// Calcul de l'offset mémoire pour piocher le pixel de la texture chargée
		ray->tex_offset = (ray->tex_y * ray->tex->size_line) + (ray->tex_x * (ray->tex->bpp / 8));
		ray->color = *(unsigned int *)(ray->tex->img_data + ray->tex_offset);

		// On pousse le pixel de texture sur ton image d'écran principale
		put_pixel(&data->img, ray->screen_x, ray->y_pixel, ray->color);
		ray->y_pixel++;
	}
}

void	render_3D(t_mlx_data * data, t_raycast *ray, int i)
{
	ray->wall_height = (int)(WIN_H / ray->perp_wall_dist); // Hauteur de la ligne à dessiner à l'écran

	// Calcul des pixels de départ et de fin
	ray->draw_start = (WIN_H / 2) - (ray->wall_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (WIN_H / 2) + (ray->wall_height / 2);
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;

	choose_tex(data, ray); // --- SÉLECTION DE LA TEXTURE SELON L'ORIENTATION ---

	// --- CALCUL DE TEX_X (La colonne correspondante de la texture) ---
	ray->wall_x -= floor(ray->wall_x); // On ne garde que la partie décimale
	ray->tex_x = (int)(ray->wall_x * (double)ray->tex->width);

	// --- PRÉPARATION DE L'INTERPOLATION VERTICALE ---
	// tex_step indique de combien de pixels de texture on avance pour 1 pixel écran
	ray->tex_step = 1.0 * ray->tex->height / ray->wall_height;
	
	// Position de départ dans la texture (gère les cas où le mur dépasse en haut de l'écran)
	ray->tex_pos = (ray->draw_start - WIN_H / 2 + ray->wall_height / 2) * ray->tex_step;

	draw_tex_on_wall(data, ray, i); // --- TRACÉ DE LA COLONNE VERTICALE AVEC TEXTURE ---
}

void	raycasting(t_mlx_data *data)
{
	int			i;
	t_raycast	ray;

	i = 0;
	while (i < WIN_W)
	{
		get_ray_vect(data, &ray, i); // Calcul du vecteur de direction du rayon
		init_dda(data, &ray); // Calcul des variables de départ du DDA
		dda_loop(data, &ray);
		fish_eye_correction(&ray); // --- CALCUL DE LA DISTANCE PERPENDICULAIRE (Anti Fish-eye) ---
		data->z_buffer[i] = ray.perp_wall_dist;
		render_3D(data, &ray, i); // --- DESSIN RENDU 3D ---
		draw_rays_minimap(data, ray); // On trace une ligne de points entre le joueur et le mur sur la minimap
		i++;
	}
	/* render_single_monster(data, &data->monster); */
	animate_and_render_monsters(data);
	
}
