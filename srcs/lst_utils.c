/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 lst_utils.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/16 12:54:03 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/21 06:27:22 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

static void		_remove_head_node(t_list **head, void (*del)(void *));
static t_list	*_find_node_and_previous(t_list *head,
					t_list *target, t_list **previous);

/** @brief Remove a node from a list
 * 
 *	Remove the node from the list and free its content.
 *	@param head The head of the list
 *	@param node The node to remove
 *	@param del The function to free the content
 *
 *	@note This function is used to remove a node from a list and update
 *	the list in contrary to ft_lstdelone that only free the node and its content.
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
	{
		previous->next = current->next;
		ft_lstdelone(current, del);
	}
}

void	ft_lstadd_or_assign(t_list **head, t_list *new_node)
{
	if (!head)
		return ;
	if (!*head)
		(*head) = new_node;
	else
		ft_lstadd_back(head, new_node);
}

static void	_remove_head_node(t_list **head, void (*del)(void *))
{
	t_list	*old_head;

	old_head = *head;
	*head = old_head->next;
	ft_lstdelone(old_head, del);
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

/** @brief Converts a linked list of strings to a null-terminated string array
* 
* Creates a new array of string pointers by copying each string from the linked
* list. Each string is duplicated using ft_strdup, making the resulting array
* independent of the original list. The array is null-terminated following
* standard C conventions.
* 
* @param lst Pointer to the first node of the linked list containing string data
* 
* @return On success, returns a pointer to a newly allocated null-terminated
*    array of string pointers. Each string is a copy of the corresponding
*    list node content. Returns NULL if:
*    - Input list is NULL
*    - Memory allocation fails for the array
*    - Memory allocation fails for any string copy (partial cleanup performed)
* 
* @note The caller is responsible for freeing the returned array and all its
*       string elements. Use a cleanup function like clean_str_array() to
*       properly deallocate.
* 
*/
char	**list_to_array(t_list *lst)
{
	char	**array;
	int		i;

	if (!lst)
		return (NULL);
	i = 0;
	array = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	while (lst)
	{
		array[i] = ft_strdup((char *)lst->content);
		if (!array[i])
		{
			print_shell_error(MALLOC_ERROR_MSG);
			return (clean_str_array(array, i));
		}
		lst = lst->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
