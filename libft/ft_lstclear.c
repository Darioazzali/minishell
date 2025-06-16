/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:01:26 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/27 15:40:29 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_node;

	if (!lst || !*lst)
		return ;
	current_node = *lst;
	if (current_node->next)
		ft_lstclear(&(current_node)->next, del);
	if (del)
		del(current_node->content);
	free(current_node);
	*lst = NULL;
}
