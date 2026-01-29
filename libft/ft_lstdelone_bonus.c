/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:59:58 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/06 05:12:20 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
/*
int	main()
{
	t_list	*lst;
	int	test;

	lst = ft_lstnew_bonus(&test);
	printf("%p\n", lst->content);
	ft_lstdelone_bonus(lst, del);
	printf("%p\n", lst->content);
	return (0);
}
*/
