/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:46:52 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/06 05:12:38 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = malloc(sizeof(t_list));
	if (!new_lst)
		return (NULL);
	new_lst->content = content;
	new_lst->next = NULL;
	return (new_lst);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
*/
int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	count = 0;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}
/*
int	main()
{
	t_list	*lst;
	int	test = 10;
	t_list	*add_front1 = ft_lstnew(&test);
	t_list	*add_front2 = ft_lstnew(&test);

	lst = ft_lstnew(&test);

	printf("size of lst : %d\n", ft_lstsize_bonus(lst));
	ft_lstadd_front(&lst, add_front1);
	printf("size of lst : %d\n", ft_lstsize_bonus(lst));
	ft_lstadd_front(&lst, add_front2);
	printf("size of lst : %d\n", ft_lstsize_bonus(lst));
//	ft_lstadd_front(&lst, add_front2);
//	printf("size of lst : %d\n", ft_lstsize_bonus(lst));
//	ft_lstadd_front(&lst, add_front1);
//	printf("size of lst : %d\n", ft_lstsize_bonus(lst));
	return (0);
}
*/
