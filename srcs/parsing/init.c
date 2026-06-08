/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:13:08 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/08 17:26:47 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_parsing	*init_parsing(void)
{
    t_parsing *parsing;

    parsing = malloc(sizeof(t_parsing));
    if (!parsing)
        return (NULL);
    parsing->no = NULL;
    parsing->so = NULL;
    parsing->we = NULL;
    parsing->ea = NULL;
    parsing->f = (t_color){-1, -1, -1};
    parsing->c = (t_color){-1, -1, -1};
    parsing->map.grid = NULL;
    parsing->map.width = 0;
    parsing->map.height = 0;
    return (parsing);
}
