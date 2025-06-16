/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:59:23 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/28 23:22:57 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*next_node;
	size_t	len;

	if (!lst)
		return (0);
	len = 1;
	next_node = lst->next;
	while (next_node)
	{
		next_node = next_node->next;
		len++;
	}
	return (len);
}
