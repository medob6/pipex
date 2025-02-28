/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:45:57 by mbousset          #+#    #+#             */
/*   Updated: 2024/11/04 10:37:16 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
#include <stdio.h>
void	print_list(t_list *lst)
{
	while (lst)
	{
		printf(" %s  ->  ", (char *)lst->content);
		lst = lst -> next;
	}
	printf("NULL\n");
}

int	main(int ac , char **av)
{
	int i = 1;
	t_list	*head = NULL;
	t_list	*new_node;
	while (i < ac)
	{
		new_node = ft_lstnew(av[i]);
		ft_lstadd_front(&head, new_node);
		i++;
	}
	print_list(head);
	return 0;
}
*/