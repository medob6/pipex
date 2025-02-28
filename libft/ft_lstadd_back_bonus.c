/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:31:13 by mbousset          #+#    #+#             */
/*   Updated: 2024/11/04 09:52:42 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
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
		ft_lstadd_back(&head, new_node);
		i++;
	}
	print_list(head);
	return 0;
}
*/