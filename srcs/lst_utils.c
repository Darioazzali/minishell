/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:54:03 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/16 12:59:38 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		_remove_head_node(t_list **head, void (*del)(void *));
static void		_remove_middle_node(t_list *previous,
					t_list *current, void (*del)(void *));
static t_list	*_find_node_and_previous(t_list *head,
					t_list *target, t_list **previous);

/** @brief Remove a node from a list
 * 
 *  Remove the node from the list and free its content.
 *  @param head The head of the list
 *  @param node The node to remove
 *  @param del The function to free the content
 *
 *  @note This function is used to remove a node from a list and update
 *  the list in contrary to ft_lstdelone that only free the node and its content.
 * */
void	ft_lstremove_node(t_list **head, t_list *node, void (*del)(void *))
{
	t_list	*current;
	t_list	*previous;

	if (!head || !*head || !node || !del)
		return ;
	current = _find_node_and_previous(*head, node, &previous);
	if (!current)
		return ;
	if (previous == NULL)
		_remove_head_node(head, del);
	else
		_remove_middle_node(previous, current, del);
}

static void	_remove_head_node(t_list **head, void (*del)(void *))
{
	t_list	*old_head;

	old_head = *head;
	*head = old_head->next;
	ft_lstdelone(old_head, del);
}

static void	_remove_middle_node(t_list *previous,
							t_list *current, void (*del)(void *))
{
	previous->next = current->next;
	ft_lstdelone(current, del);
}

static t_list	*_find_node_and_previous(t_list *head,
								t_list *target, t_list **previous)
{
	t_list	*current;

	current = head;
	*previous = NULL;
	while (current)
	{
		if (target == current)
			return (current);
		*previous = current;
		current = current->next;
	}
	return (NULL);
}
