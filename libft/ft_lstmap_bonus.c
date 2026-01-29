/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 03:47:13 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/06 19:33:46 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_elem;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	content = f(lst->content);
	new = ft_lstnew(content);
	if (!new)
		return (free(content), NULL);
	new_elem = new;
	while (lst && lst->next)
	{
		content = f(lst->next->content);
		new_elem->next = ft_lstnew(content);
		if (!new_elem->next)
		{
			del(content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		new_elem = new_elem->next;
		lst = lst->next;
	}
	return (new);
}
