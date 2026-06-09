/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:22:40 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/09 18:20:23 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

//monster and door

//struct door 
// typedef struct s_door
// {
//     int     x;
//     int     y;
//     int     open;  // 0 fermée, 1 ouverte
// }   t_door;

int check_door(t_parsing *parsing, char *line, int i) // probleme : a ce moment la du check ma map nest pas completement cree donc jai pas acces a x+1 et y+1 
{
    //peut pas etre a width = 0 ou width max/ idem pour height
    if ((grid[y][x-1] == '1' && grid[y][x+1] == '1') || (grid[y-1][x] == '1' && grid[y+1][x] == '1')) //porte entouree dun mur de chaque cote
    {
        parsing->door.x = line[i];
        parsing->door.y = parsing->map.height - 1;
        parsing->door.open = 0;
    }
    else
        return (0); // a gerer map nn valide etc printerr (bad door pos)
}

int new_monster()
{
    parsing->monster.x = line[i];
    parsing->monster.y = parsing->map.height - 1;
    return (1);
}
