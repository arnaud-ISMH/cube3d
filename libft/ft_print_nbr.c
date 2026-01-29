/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:28:08 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/07 09:32:33 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr(int nbr)
{
	char	*nb;
	int		size;

	nb = ft_itoa(nbr);
	size = ft_print_str(nb);
	free(nb);
	return (size);
}
