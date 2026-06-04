/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:13:08 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/04 16:16:01 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
    parsing->f = -1;
    parsing->c = -1;
    parsing->map.grid = NULL;
    parsing->map.width = 0;
    parsing->map.height = 0;
    printf("%p, %p, %p, %p, %i, %i\n", parsing->no, parsing->so, parsing->we, parsing->ea, parsing->f, parsing->c);
    return (parsing);
}
